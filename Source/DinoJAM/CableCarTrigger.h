// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Objective.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "CableCarTrigger.generated.h"

UCLASS()
class DINOJAM_API ACableCarTrigger : public AObjective, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACableCarTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* CableCarExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULevelSequence* CableCarSequence;

	UFUNCTION()
	void OnCableCarSequenceFinished();

	UPROPERTY(BlueprintReadWrite)
	APlayerCharacter* PlayerCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APS1Character* Interactor) override;
};
