// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"

UENUM()
enum EDialogOwner
{
	PLAYER,
	NPC
};

UCLASS(Blueprintable, EditInlineNew)
class UDialogItem: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundBase* Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TextLine")
	FString TextLine;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Timer")
	float DelayToNextDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Flow")
	bool AutomaticPlayNextDialog = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* NPCAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* PlayerAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Facial Expression")
	class UMaterialInterface* NPCFaceExpressionMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Facial Expression")
    int NPCFaceMaterialIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Facial Expression")
	class UMaterialInterface* PlayerFaceExpressionMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TEnumAsByte<EDialogOwner> DialogOwner;
};

DECLARE_DELEGATE_OneParam(FOnDialogFinish, UDialogItem*);

/**
* 
*/
UCLASS()
class DINOJAM_API ADinoJAMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/////////////////////////////////////////////
	///
	/// DIALOG SYSTEM
	///
	/////////////////////////////////////////////
	void PlayNextDialog();
	
	void StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish);

	void StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish, APlayerCharacter* PlayerCharacter, APS1Character* NPC);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<UDialogItem>> Dialogs;

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
	/// LEVEL 2 SEQUENCES
	///
	/////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sequences")
	class ULevelSequence* GateLevelSequence;
	
protected:
	/////////////////////////////////////////////
	///
	/// SOUND STUFF
	///
	//////////////////////////////////////////////
	UPROPERTY()
	class UAudioComponent* DialogAudioComponent;

	UPROPERTY()
	struct FTimerHandle CurrentDialogSoundTimerHandle;
	void OnDialogSoundFinish();

	//////////////////////////////////////////////
	///
	/// DIALOG SYSTEM
	///
	//////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> WidgetDialogTextReference;

	UPROPERTY()
	class UDialogItem* CurrentDialogItem;
	
	UPROPERTY()
	class UUserWidget* WidgetDialogText;

	UPROPERTY()
	class UTextBlock* WidgetDialogTextBlock;

	UPROPERTY()
	class UTextBlock* WidgetCharacterNameTextBlock;
	
	UPROPERTY()
	struct FTimerHandle DelayToNextDialogTimerHandle;

	void PlayDialog(UDialogItem* DialogItem);

	FOnDialogFinish OnDialogFinish;
	
	void OnDialogSystemFinish(UDialogItem* DialogItem);

	void SetupDialogSystemWidget();

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
};