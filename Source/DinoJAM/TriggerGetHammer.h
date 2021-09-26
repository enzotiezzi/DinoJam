// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Engine/TriggerSphere.h"
#include "TriggerGetHammer.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ATriggerGetHammer : public ATriggerSphere, public IInteractable
{
	GENERATED_BODY()

public:
	ATriggerGetHammer();
	
	virtual void Interact(ACharacter* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;
	
};
