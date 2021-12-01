// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

#include "DialogSystem.h"
#include "InventorySystem.h"
#include "LevelSequencePlayer.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

ADinoJAMGameModeBase::ADinoJAMGameModeBase()
{
}

void ADinoJAMGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		MyGameInstance->InventorySystem->CurrentWorld = GetWorld();
		MyGameInstance->QuestSystem->CurrentWorld = GetWorld();
	}

	if(DialogSystemReference)
	{
		DialogSystem = Cast<UDialogSystem>(DialogSystemReference.GetDefaultObject());

		DialogSystem->CurrentWorld = GetWorld();
		DialogSystem->SetupDialogSystemWidget();
	}
	
	SetupTitleScreenWidget();
	SetupPauseMenuWidget();
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
			PlayerCharacter->StartWavingAnimationMontage();

			if(APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
			{
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(TitleScreen->GetWidgetFromName("Button_Start")->TakeWidget());
				
				PlayerController->SetShowMouseCursor(true);
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
}

void ADinoJAMGameModeBase::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "L_KarenOutdoor");

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(PlayerCharacter)
	{
		if(APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
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

			PauseMenuButtons = TArray<class UButton*, TFixedAllocator<4>>();
			PauseMenuButtons.Add(PauseMenuInventoryButton);
			PauseMenuButtons.Add(PauseMenuResumeButton);
			PauseMenuButtons.Add(PauseMenuSaveButton);
			PauseMenuButtons.Add(PauseMenuQuitButton);

			PauseMenuButtonsNormalStates = TArray<struct FSlateBrush, TFixedAllocator<4>>();
			PauseMenuButtonsNormalStates.Add(PauseMenuInventoryButton->WidgetStyle.Normal);
			PauseMenuButtonsNormalStates.Add(PauseMenuResumeButton->WidgetStyle.Normal);
			PauseMenuButtonsNormalStates.Add(PauseMenuSaveButton->WidgetStyle.Normal);
			PauseMenuButtonsNormalStates.Add(PauseMenuQuitButton->WidgetStyle.Normal);

			PauseMenuButtonsHoveredStates = TArray<struct FSlateBrush, TFixedAllocator<4>>();
			PauseMenuButtonsHoveredStates.Add(PauseMenuInventoryButton->WidgetStyle.Hovered);
			PauseMenuButtonsHoveredStates.Add(PauseMenuResumeButton->WidgetStyle.Hovered);
			PauseMenuButtonsHoveredStates.Add(PauseMenuSaveButton->WidgetStyle.Hovered);
			PauseMenuButtonsHoveredStates.Add(PauseMenuQuitButton->WidgetStyle.Hovered);
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

		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	GetWorld()->GetTimerManager().ClearTimer(PauseMenuUITimerHandle);
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

			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			InputMode.SetWidgetToFocus(PauseMenuWidget->GetWidgetFromName("Pause_Menu_Button_Inventory")->TakeWidget());
			
			PlayerController->SetInputMode(InputMode);

			if(!PauseMenuUITimerHandle.IsValid())
				GetWorld()->GetTimerManager().SetTimer(PauseMenuUITimerHandle, this, &ADinoJAMGameModeBase::TickPauseMenuUI, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

void ADinoJAMGameModeBase::TickPauseMenuUI()
{
	for(int i = 0; i < PauseMenuButtons.Num(); i++)
	{
		UButton* CurrentButton = PauseMenuButtons[i];

		if(CurrentButton->HasKeyboardFocus())
		{
			CurrentButton->WidgetStyle.Normal = PauseMenuButtonsHoveredStates[i];
		}
		else
		{
			CurrentButton->WidgetStyle.Normal = PauseMenuButtonsNormalStates[i];
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
		if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			MyGameInstance->CurrentPlayerCharacter->StopMoving();
		}
		
		LevelSequencePlayer->OnFinished.AddDynamic(this, &ADinoJAMGameModeBase::OnFadeOutFinish);
		
		LevelSequencePlayer->Play();
	}
}

void ADinoJAMGameModeBase::OnFadeOutFinish()
{
	if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGameInstance->CurrentPlayerCharacter->ContinueMoving();
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}