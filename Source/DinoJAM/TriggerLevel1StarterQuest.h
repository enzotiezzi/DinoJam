// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "Interactable.h"
#include "PS1Character.h"
#include "Engine/TriggerSphere.h"
#include "TriggerLevel1StarterQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ATriggerLevel1StarterQuest : public ATriggerSphere, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void PreviewInteraction(APS1Character* Interactor) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	ACharacter* CurrentInteractor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	class APS1Character* Karen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objective")
	class AObjective* Objective;

	FTimerHandle RotateToKarenTimerHandle;

	void OnRotateToKaren();

	void StopRotateToKaren(class UDialogItem* DialogItem);
};
