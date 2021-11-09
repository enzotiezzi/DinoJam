// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1PlayPianoQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1PlayPianoQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> StartDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> AfterPlayPianoDialog;

	void ExecuteDialogAfterPlayPianoFinish(UDialogItem* DialogItem);

	void ExecuteOnStarterDialogFinish(UDialogItem* DialogItem);
};
