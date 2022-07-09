// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Dialog.h"
#include "UObject/NoExportTypes.h"
#include "DialogSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UDialogSystem : public UObject
{
	GENERATED_BODY()

public:
	UDialogSystem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWorld* CurrentWorld;

	/////////////////////////////////////////////
	///
	/// DIALOG SYSTEM
	///
	/////////////////////////////////////////////
	void PlayNextDialog();
	
	void StartDialogSystem(class UDialog* Dialog);

	void StartDialogSystem(class UDialog* Dialog, APlayerCharacter* PlayerCharacter, APS1Character* NPC);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<UDialogItem>> Dialogs;
	
	void SetupDialogSystemWidget();

protected:
	//////////////////////////////////////////////
	///
	/// DIALOG SYSTEM
	///
	//////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> WidgetDialogTextReference;

	UPROPERTY()
	class UDialog* CurrentDialog;
	
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
	
	/////////////////////////////////////////////
	///
	/// SOUND STUFF
	///
	//////////////////////////////////////////////
	UPROPERTY()
	class UAudioComponent* DialogAudioComponent;

	UPROPERTY()
	class UAudioComponent* MusicAudioComponent;

	UPROPERTY()
	struct FTimerHandle CurrentDialogSoundTimerHandle;
	void OnDialogSoundFinish();

	/////////////////////////////////////////////
	///
	/// SEQUENCE
	///
	/////////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ULevelSequencePlayer* CurrentSequencePlayer;
};
