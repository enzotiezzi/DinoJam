// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dialog.h"
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
	TMap<UClass*, TSubclassOf<class UDialog>> CharactersDialog;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	TSubclassOf<UQuest> NextQuest;

	virtual void OnQuestFinish(UWorld* World);

	virtual void OnQuestStart(UWorld* World);
	
	virtual void CompleteQuest(UWorld* World);
	
	virtual TSubclassOf<class UDialog> GetDialog(UClass* Class)
	{
		return CharactersDialog[Class];
	};
};
