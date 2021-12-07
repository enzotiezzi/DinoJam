// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Objective.h"
#include "TriggerPlaceMrAussichtPack.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ATriggerPlaceMrAussichtPack : public AObjective, public IInteractable
{
	GENERATED_BODY()

public:
	ATriggerPlaceMrAussichtPack();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void Interact(APS1Character* Interactor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;
};
