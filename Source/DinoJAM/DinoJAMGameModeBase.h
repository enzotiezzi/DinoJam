// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"

UENUM()
enum ELEVEL1_QUESTS
{
	SETUP_PIANO,
	FIND_HAMMER,
	BUILD_PIANO
};

UENUM()
enum EDialogSystemAnimationOwner
{
	SELF,
	PLAYER
};

USTRUCT(BlueprintType)
struct FDialogItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundBase* Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TextLine")
	FString TextLine;

	UPROPERTY(VisibleInstanceOnly ,BlueprintReadWrite, Category="Character")
	class ACharacter* OwnerCharacter;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Character")
	class ACharacter* PlayerCharacter;

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

DECLARE_DELEGATE_OneParam(FOnDialogFinish, FDialogItem);

/**
* 
*/
UCLASS()
class DINOJAM_API ADinoJAMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	// LEVELS QUESTS AND OBJECTIVES
protected:
	TEnumAsByte<ELEVEL1_QUESTS> CurrentLevel1Quest = ELEVEL1_QUESTS::SETUP_PIANO;
	bool bIsPianoSetup = false;
	bool bFoundHammer = false;
	bool bIsPianoBuilt = false;
	
public:
	virtual void BeginPlay() override;
	
	void PlayNextDialog();
	
	void StartDialogSystem(TArray<struct FDialogItem> NewDialogs, FOnDialogFinish OnNewDialogFinish);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> WidgetDialogTextReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<struct FDialogItem> Dialogs;

protected:
	UPROPERTY()
	class UAudioComponent* DialogAudioComponent;
	
	UPROPERTY()
	struct FDialogItem CurrentDialogItem;
	
	UPROPERTY()
	class UUserWidget* WidgetDialogText;

	UPROPERTY()
	class UTextBlock* WidgetDialogTextBlock;

	UPROPERTY()
	struct FTimerHandle CurrentDialogSoundTimerHandle;
	void OnDialogSoundFinish();

	UPROPERTY()
	struct FTimerHandle DelayToNextDialogTimerHandle;

	void PlayDialog(FDialogItem DialogItem);

	FOnDialogFinish OnDialogFinish;

	void TestDialogFinish(FDialogItem DialogItem);
};