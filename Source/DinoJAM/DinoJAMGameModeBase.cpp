// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ADinoJAMGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetupDialogSystemWidget();
	SetupTitleScreenWidget();
}

void ADinoJAMGameModeBase::SetupDialogSystemWidget()
{
	if(WidgetDialogTextReference)
	{
		WidgetDialogText = CreateWidget<UUserWidget>(GetWorld(), WidgetDialogTextReference);

		if(WidgetDialogText)
		{
			WidgetDialogTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_Dialog"));
		}
	}
}

void ADinoJAMGameModeBase::StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		StartDialogSystem(NewDialogs, OnNewDialogFinish, MyGameInstance->CurrentPlayerCharacter, MyGameInstance->CurrentNPC);
	}
}

void ADinoJAMGameModeBase::StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish, APlayerCharacter* PlayerCharacter, ACharacter* NPC)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		Dialogs = NewDialogs;
		OnDialogFinish = OnNewDialogFinish;
		MyGameInstance->CurrentPlayerCharacter = PlayerCharacter;
		MyGameInstance->CurrentNPC = NPC;

		MyGameInstance->CurrentPlayerCharacter->StartDialog();

		if(Dialogs.Num() > 0)
		{
			UDialogItem* DialogItem = Dialogs[0].GetDefaultObject();
			Dialogs.RemoveAt(0);

			PlayDialog(DialogItem);
		}
	}
}

void ADinoJAMGameModeBase::PlayDialog(UDialogItem* DialogItem)
{
	if(DialogItem)
	{
		if(DialogAudioComponent != nullptr)
			DialogAudioComponent->Stop();
	
		CurrentDialogItem = DialogItem;
		CurrentDialogItem->World = GetWorld();

		if(CurrentDialogSoundTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

		if(DelayToNextDialogTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
		if(DialogItem->Sound)
		{
			GetWorld()->GetTimerManager().SetTimer(CurrentDialogSoundTimerHandle, this, &ADinoJAMGameModeBase::OnDialogSoundFinish, DialogItem->Sound->Duration);

			DialogAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogItem->Sound);
		}

		if(!WidgetDialogText->IsInViewport())
			WidgetDialogText->AddToViewport();

		WidgetDialogTextBlock->SetText(FText::FromString(DialogItem->TextLine));
	}
}

void ADinoJAMGameModeBase::OnDialogSoundFinish()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

	if(CurrentDialogItem->AutomaticPlayNextDialog)
	{
		if(Dialogs.Num() > 0)
		{
			if(DelayToNextDialogTimerHandle.IsValid())
				GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);

			GetWorld()->GetTimerManager().SetTimer(DelayToNextDialogTimerHandle, this, &ADinoJAMGameModeBase::PlayNextDialog, CurrentDialogItem->DelayToNextDialog);
		}
	}
}

void ADinoJAMGameModeBase::PlayNextDialog()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
	if(Dialogs.Num() > 0)
	{
		UDialogItem* DialogItem = Dialogs[0].GetDefaultObject();
		Dialogs.RemoveAt(0);

		PlayDialog(DialogItem);
	}
	else
	{
		if(WidgetDialogText)
		{
			WidgetDialogTextBlock->SetText(FText::FromString(""));

			if(WidgetDialogText->IsInViewport())
				WidgetDialogText->RemoveFromViewport();
		}

		if(DialogAudioComponent != nullptr)
			DialogAudioComponent->Stop();

		OnDialogSystemFinish(CurrentDialogItem);
	}
}

void ADinoJAMGameModeBase::OnDialogSystemFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentPlayerCharacter)
			MyGameInstance->CurrentPlayerCharacter->OnDialogFinish();
	
		if(OnDialogFinish.IsBound())
			OnDialogFinish.Execute(CurrentDialogItem);
	}
}

void ADinoJAMGameModeBase::SetupTitleScreenWidget()
{
	if(TitleScreenReference)
	{
		TitleScreen = CreateWidget<UUserWidget>(GetWorld(), TitleScreenReference);

		if(TitleScreen)
		{
			StartButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Start"));
			ContinueButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Continue"));
			QuitButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Quit"));

			StartButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::StartGame);
			QuitButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::QuitGame);
		}
	}
}

void ADinoJAMGameModeBase::StartTitleScreen()
{
	SetupTitleScreenWidget();
	
	if(TitleScreen)
	{
		TitleScreen->AddToViewport();

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
		if(PlayerCharacter)
		{
			StartDialogSystem(TArray<TSubclassOf<UDialogItem>>(), FOnDialogFinish(), PlayerCharacter, nullptr);

			PlayerCharacter->StartWavingAnimationMontage();

			if(APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
			{
				PlayerController->SetShowMouseCursor(true);
			}
		}
	}
}

void ADinoJAMGameModeBase::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "L_KarenOutdoor");
}

void ADinoJAMGameModeBase::QuitGame()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(Character)
		UKismetSystemLibrary::QuitGame(GetWorld(), Cast<APlayerController>(Character->GetController()), EQuitPreference::Quit, true);
}
