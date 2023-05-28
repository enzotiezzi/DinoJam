// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAM/Interactable.h"
#include "Engine/TriggerSphere.h"
#include "Level3DoorTrigger.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ALevel3DoorTrigger : public ATriggerSphere, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(APS1Character* Interactor) override;
};
