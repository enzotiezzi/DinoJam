// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

#include "InventorySystem.h"
#include "LevelSequencePlayer.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "PS1Character.h"
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
	SetupPauseMenuWidget();
}

void ADinoJAMGameModeBase::SetupDialogSystemWidget()
{
	if(WidgetDialogTextReference)
	{
		WidgetDialogText = CreateWidget<UUserWidget>(GetWorld(), WidgetDialogTextReference);

		if(WidgetDialogText)
		{
			WidgetDialogTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_Dialog"));
			WidgetCharacterNameTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_CharacterName"));
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

void ADinoJAMGameModeBase::StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish, APlayerCharacter* PlayerCharacter, APS1Character* NPC)
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
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			if(MyGameInstance->CurrentPlayerCharacter)
			{
				if(DialogItem->PlayerAnimation)
					MyGameInstance->CurrentPlayerCharacter->PlayAnimMontage(DialogItem->PlayerAnimation);
				else
					MyGameInstance->CurrentPlayerCharacter->StopAnimMontage();

				if(DialogItem->PlayerFaceExpressionMaterial)
					MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(MyGameInstance->CurrentPlayerCharacter->FaceMaterialIndex, DialogItem->PlayerFaceExpressionMaterial);
			}

			if(MyGameInstance->CurrentNPC)
			{
				if(DialogItem->NPCAnimation)
					MyGameInstance->CurrentNPC->PlayAnimMontage(DialogItem->NPCAnimation);
				else
					MyGameInstance->CurrentNPC->StopAnimMontage();
				
				if(DialogItem->NPCFaceExpressionMaterial)
					MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, DialogItem->NPCFaceExpressionMaterial);
				else
					MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
			}

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

			FText DialogOwnerText;

			if(DialogItem->DialogOwner == EDialogOwner::PLAYER)
				DialogOwnerText = FText::FromString(MyGameInstance->CurrentPlayerCharacter->CharacterName);
			else
				DialogOwnerText = FText::FromString(MyGameInstance->CurrentNPC->CharacterName);

			WidgetCharacterNameTextBlock->SetText(DialogOwnerText);
			WidgetDialogTextBlock->SetText(FText::FromString(DialogItem->TextLine));
		}
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
			TitleScreenStartButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Start"));
			TitleScreenContinueButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Continue"));
			TitleScreenQuitButton = Cast<UButton>(TitleScreen->GetWidgetFromName("Button_Quit"));

			TitleScreenStartButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::StartGame);
			TitleScreenQuitButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::QuitGame);
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

void ADinoJAMGameModeBase::SetupPauseMenuWidget()
{
	if(PauseMenuWidgetReference)
	{
		PauseMenuWidget = CreateWidget(GetWorld(), PauseMenuWidgetReference);

		if(PauseMenuWidget)
		{
			PauseMenuInventoryButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("Pause_Menu_Button_Inventory"));
			PauseMenuResumeButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("Pause_Menu_Button_Resume"));
			PauseMenuSaveButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("Pause_Menu_Button_Save"));
			PauseMenuQuitButton = Cast<UButton>(PauseMenuWidget->GetWidgetFromName("Pause_Menu_Button_Quit"));

			PauseMenuInventoryButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::OpenInventory);
			PauseMenuResumeButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::ResumeGame);
			PauseMenuQuitButton->OnClicked.AddDynamic(this, &ADinoJAMGameModeBase::QuitGame);
		}
	}
}

void ADinoJAMGameModeBase::OpenInventory()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		MyGameInstance->InventorySystem->ShowInventory();
	}
}

void ADinoJAMGameModeBase::ResumeGame()
{
	if(PauseMenuWidget)
	{
		if(PauseMenuWidget->IsInViewport())
			PauseMenuWidget->RemoveFromViewport();
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		MyGameInstance->InventorySystem->HideInventory();

		APlayerController* PlayerController = Cast<APlayerController>(MyGameInstance->CurrentPlayerCharacter->GetController());

		if(PlayerController)
			PlayerController->SetShowMouseCursor(false);
	}
}

void ADinoJAMGameModeBase::PauseGame()
{
	if(PauseMenuWidget)
	{
		if(!PauseMenuWidget->IsInViewport())
		{
			PauseMenuWidget->AddToViewport(2);
		}
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentPlayerCharacter)
		{
			APlayerController* PlayerController = Cast<APlayerController>(MyGameInstance->CurrentPlayerCharacter->GetController());

			if(PlayerController)
				PlayerController->SetShowMouseCursor(true);
		}
	}
}

void ADinoJAMGameModeBase::ChangeLevel(FName LevelName)
{
	NextLevelName = LevelName;
	
	ALevelSequenceActor* LevelSequenceActor;
	
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), FadeOutLevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if(LevelSequencePlayer)
	{
		LevelSequencePlayer->OnFinished.AddDynamic(this, &ADinoJAMGameModeBase::OnFadeOutFinish);
		
		LevelSequencePlayer->Play();
	}
}

void ADinoJAMGameModeBase::OnFadeOutFinish()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}
