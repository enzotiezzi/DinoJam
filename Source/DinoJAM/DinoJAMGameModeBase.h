// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Level1Objectives.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "AudioManager.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"


/**
* 
*/
UCLASS()
class DINOJAM_API ADinoJAMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADinoJAMGameModeBase();
	
	virtual void BeginPlay() override;

	//////////////////////////////////////////////
	///
	/// DIALOG SYSTEM
	///
	//////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialogSystem> DialogSystemReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Dialog System")
	class UDialogSystem* DialogSystem;

	//////////////////////////////////////////////
	///
	/// TITLE SCREEN
	///
	//////////////////////////////////////////////
	void StartTitleScreen();

	//////////////////////////////////////////////
	///
	/// PAUSE MENU
	///
	//////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pause Menu")
	TSubclassOf<class UUserWidget> PauseMenuWidgetReference;
	
	void SetupPauseMenuWidget();

	void PauseGame();

	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void ResumeGame();

	/////////////////////////////////////////////
	///
	/// GENERAL SEQUENCES
	///
	/////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fade")
	class ULevelSequence* FadeInLevelSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fade")
	class ULevelSequence* FadeOutLevelSequence;

	UPROPERTY(BlueprintReadWrite)
	FName NextLevelName;
	
	void ChangeLevel(FName LevelName);

	UFUNCTION()
	void OnFadeOutFinish();

	/////////////////////////////////////////////
	///
	/// LEVEL 2 SEQUENCES
	///
	/////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sequences")
	class ULevelSequence* GateLevelSequence;

	/////////////////////////////////////////////
	///
	/// AUDIO MANAGER
	///
	/////////////////////////////////////////////
	UPROPERTY(BlueprintReadwrite)
	class AAudioManager* AudioManager;
	
protected:
	///////////////////////////////////////////////////
	///
	/// TITLE SCREEN
	///
	///////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Title Screen")
	TSubclassOf<class UUserWidget> TitleScreenReference;

	UPROPERTY(BlueprintReadWrite, Category="Title Screen")
	class UUserWidget* TitleScreen;
	
	UPROPERTY()
	class UButton* TitleScreenStartButton;

	UPROPERTY()
	class UButton* TitleScreenContinueButton;

	UPROPERTY()
	class UButton* TitleScreenQuitButton;
	
	void SetupTitleScreenWidget();

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	////////////////////////////////////////////////
	///
	/// PAUSE MENU
	///
	////////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* PauseMenuWidget;

	UPROPERTY(BlueprintReadWrite)
	class UButton* PauseMenuInventoryButton;

	UPROPERTY(BlueprintReadWrite)
	class UButton* PauseMenuResumeButton;

	UPROPERTY(BlueprintReadWrite)
	class UButton* PauseMenuSaveButton;

	UPROPERTY(BlueprintReadWrite)
	class UButton* PauseMenuQuitButton;

	UPROPERTY()
	TArray<class UButton*> PauseMenuButtons;
	
	UPROPERTY()
	TArray<struct FSlateBrush> PauseMenuButtonsNormalStates;

	UPROPERTY()
	TArray<struct FSlateBrush> PauseMenuButtonsHoveredStates;

	struct FTimerHandle PauseMenuUITimerHandle;
	void TickPauseMenuUI();
};