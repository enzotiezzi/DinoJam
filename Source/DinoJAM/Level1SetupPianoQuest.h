// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1SetupPianoQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1SetupPianoQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<TSubclassOf<UDialogItem>> DialogStartQuest;
};
