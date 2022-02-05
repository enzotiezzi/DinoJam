// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level2SetupGlassesQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel2SetupGlassesQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Starting Dialog")
	TSubclassOf<UDialog> StartingDialog;
};
