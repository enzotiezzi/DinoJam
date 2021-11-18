// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UQuestSystem : public UObject
{
	GENERATED_BODY()

public:
	UQuestSystem();

	UPROPERTY(BlueprintReadWrite)
	UWorld* CurrentWorld;

	void StartQuest(class UQuest* Quest);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	TSubclassOf<class UQuest> CurrentQuest;

	UQuest* GetCurrentQuest() const
	{
		return qCurrentQuest;
	}
protected:
	UPROPERTY(BlueprintReadWrite)
	class UQuest* qCurrentQuest;
};
