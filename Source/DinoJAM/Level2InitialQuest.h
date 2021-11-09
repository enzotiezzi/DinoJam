// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level2InitialQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel2InitialQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> StartingDialog;

	void OnStartingDialogFinish(class UDialogItem* DialogItem);
};
