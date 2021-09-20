// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.generated.h"

UINTERFACE(Blueprintable)
class DINOJAM_API UInteractable : public UInterface
{
	GENERATED_BODY()
	
};

class IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(ACharacter* Interactor);
};