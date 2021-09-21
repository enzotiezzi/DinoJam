// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	TSubclassOf<class UQuest> CurrentQuest;
	
	UPROPERTY()
	class UQuest* qCurrentQuest;
	
	virtual void BeginPlay() override;
	
	void PlayNextDialog();
	
	void StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish);

	void StartQuest(UQuest* Quest);
	
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
	
	void OnDialogSystemFinish(UDialogItem* DialogItem);
};