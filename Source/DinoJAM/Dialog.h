// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "UObject/NoExportTypes.h"
#include "Dialog.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UDialog();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DialogSystem")
	TArray<TSubclassOf<class UDialogItem>> Dialogs;

	FOnDialogFinish OnDialogFinish;

	UFUNCTION()
	virtual void OnDialogFinished(class UDialogItem* DialogItem);
};
