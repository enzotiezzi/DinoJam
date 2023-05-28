// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAM/Interactable.h"
#include "DinoJAM/PS1Character.h"
#include "DrMosca.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ADrMosca : public APS1Character, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(APS1Character* Interactor) override;
};
