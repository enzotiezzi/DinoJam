// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1AskForHammerQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1AskForHammerQuest : public UQuest
{
	GENERATED_BODY()
	
public:
	virtual void OnQuestStart(UWorld* World) override;

	virtual TArray<TSubclassOf<class UDialogItem>> GetDialogBasedOnComplexCondition() override;

	virtual FOnDialogFinish GetOnDialogFinishBasedOnComplexCondition() override;
	
	bool bHaveHammer = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<class UDialogItem>> PreDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<class UDialogItem>> DontHaveHammerDialog;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<class UDialogItem>> HaveHammerDialog;

	FOnDialogFinish OnHaveHammerDialogFinish;
};