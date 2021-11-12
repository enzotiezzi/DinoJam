// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.h"
#include "PS1Character.h"
#include "Cyclop.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ACyclop : public APS1Character, public IInteractable
{
	GENERATED_BODY()

public:
	ACyclop();

	virtual void Interact(APS1Character* Interactor) override;
};
