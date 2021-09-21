// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "UQuest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UQuest : public UObject
{
	GENERATED_BODY()

public:
	UQuest();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ID")
	int Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Name")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	bool bCompleted = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DialogSystem")
	TArray<TSubclassOf<UDialogItem>> Dialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	TSubclassOf<UQuest> NextQuest;

	FOnDialogFinish OnDialogFinish;

	UFUNCTION()
	virtual bool CheckQuestComplention()
	{
		return bCompleted;
	}

	virtual void OnQuestFinish();

	virtual void OnQuestStart();
	
	virtual void CompleteQuest();
};
