// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "MrAussichtGlasses.h"
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

	virtual void Interact(APS1Character* Interactor) override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Overlap")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spawn Area")
	UArrowComponent* SpawnArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Glasses")
	TSubclassOf<AMrAussichtGlasses> Glasses;
};
