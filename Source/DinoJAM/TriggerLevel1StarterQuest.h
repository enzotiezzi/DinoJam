// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
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
	virtual void PreviewInteraction(ACharacter* Interactor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character")
	class ACharacter* Karen;
};
