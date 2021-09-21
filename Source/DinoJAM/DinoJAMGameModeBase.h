// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"

UENUM()
enum ELEVEL1_QUESTS
{
	BEFORE_LEVEL,
	SETUP_PIANO,
	BEFORE_FIND_HAMMER,
	FIND_HAMMER,
	BUILD_PIANO,
	SIGN_PAPER,
	LEVEL_FINISH
};

UENUM()
enum EDialogSystemAnimationOwner
{
	SELF,
	PLAYER
};

UCLASS(Blueprintable, EditInlineNew)
class UDialogItem: public UObject
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundBase* Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TextLine")
	FString TextLine;

	UPROPERTY(VisibleInstanceOnly ,BlueprintReadWrite, Category="Character")
	class ACharacter* OwnerCharacter;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Character")
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Timer")
	float DelayToNextDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Flow")
	bool AutomaticPlayNextDialog = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* Animation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	class UAnimMontage* PlayerAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	TEnumAsByte<EDialogSystemAnimationOwner> AnimationOwner;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogBeforeLevel;
	FOnDialogFinish OnDialogBeforeLevelFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogBeforeSetupPiano;
	FOnDialogFinish OnDialogBeforeSetupPianoFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogDuringSetupPiano;
	FOnDialogFinish OnDialogDuringSetupPianoFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogBeforeFindHammer;
	FOnDialogFinish OnDialogBeforeFindHammerFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogFindHammer;
	FOnDialogFinish OnDialogFindHammerFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogNoHammer;
	FOnDialogFinish OnDialogNoHammerFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogFoundHammer;
	FOnDialogFinish OnDialogFoundHammerFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogBuildPiano;
	FOnDialogFinish OnDialogBuildPianoFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogPlayPiano;
	FOnDialogFinish OnDialogPlayPianoFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogSignPaper;
	FOnDialogFinish OnDialogSignPaperFinish;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogLevelComplete;
	FOnDialogFinish OnDialogLevelCompleteFinish;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LEVEL 1 QUESTS")
	TEnumAsByte<ELEVEL1_QUESTS> CurrentLevel1Quest = ELEVEL1_QUESTS::SETUP_PIANO;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LEVEL 1 QUESTS")
	bool bIsPianoSetup = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LEVEL 1 QUESTS")
	bool bFoundHammer = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="LEVEL 1 QUESTS")
	bool bIsPianoBuilt = false;
	
	virtual void BeginPlay() override;
	
	void PlayNextDialog();
	
	void StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> WidgetDialogTextReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<UDialogItem>> Dialogs;

protected:
	UPROPERTY()
	class UAudioComponent* DialogAudioComponent;
	
	UPROPERTY()
	class UDialogItem* CurrentDialogItem;
	
	UPROPERTY()
	class UUserWidget* WidgetDialogText;

	UPROPERTY()
	class UTextBlock* WidgetDialogTextBlock;

	UPROPERTY()
	struct FTimerHandle CurrentDialogSoundTimerHandle;
	void OnDialogSoundFinish();

	UPROPERTY()
	struct FTimerHandle DelayToNextDialogTimerHandle;

	void PlayDialog(UDialogItem* DialogItem);

	FOnDialogFinish OnDialogFinish;

	void TestDialogFinish(UDialogItem* DialogItem);

	// DIALOG FINISH
	void OnDialogBeforeLevelFinished(UDialogItem* DialogItem);
};