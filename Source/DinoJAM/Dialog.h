// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "UObject/NoExportTypes.h"
#include "Dialog.generated.h"


UENUM()
enum EDialogOwner
{
	PLAYER,
	NPC
};

USTRUCT(BlueprintType)
struct FFaceExpression
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Index;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMaterialInterface* FaceExpressionMaterial;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TextLine")
	FString NPCName;
	
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
	class UMaterialInterface* PlayerFaceExpressionMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Facial Expression")
	TArray<struct FFaceExpression> ExtraFaceExpressions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TEnumAsByte<EDialogOwner> DialogOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sequence")
	class ULevelSequence* Sequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sequence")
	bool HidePlayerDuringSequence = false;

	//////////////////////////////////////
	///
	/// MUSIC
	/// 
	/////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Music")
	class USoundBase* DialogMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Music")
	bool StopPreviousDialogMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Music")
	bool RestartEnvironmentMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Music")
	bool PauseEnvironmentMusic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Music")
	bool StopEnvironmentMusic;
};

DECLARE_DELEGATE_OneParam(FOnDialogFinish, UDialogItem*);

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UDialog();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DialogSystem")
	TArray<TSubclassOf<class UDialogItem>> Dialogs;

	FOnDialogFinish OnDialogFinish;

	UFUNCTION()
	virtual void OnDialogFinished(class UDialogItem* DialogItem);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bRestoreNPCState = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bRestorePlayerState = true;
};
