// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level2FindAussichtQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel2FindAussichtQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UDialog> StartQuestDialog;
};