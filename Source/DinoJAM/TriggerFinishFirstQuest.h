// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "TriggerFinishFirstQuest.generated.h"

UCLASS()
class DINOJAM_API ATriggerFinishFirstQuest : public AObjective, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerFinishFirstQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APS1Character* Interactor) override;

};
