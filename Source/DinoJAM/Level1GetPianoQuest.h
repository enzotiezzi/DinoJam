// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1GetPianoQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1GetPianoQuest : public UQuest
{
	GENERATED_BODY()

protected:
	void ExecuteOnDialogFinish(UDialogItem* DialogItem);

	virtual void OnQuestStart(UWorld* World) override;
};
