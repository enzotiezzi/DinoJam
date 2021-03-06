// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Objective.h"
#include "TriggerPlayPiano.h"
#include "GameFramework/Actor.h"
#include "TriggerPlacePianoBox.generated.h"

UCLASS()
class DINOJAM_API ATriggerPlacePianoBox : public AObjective, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerPlacePianoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	///////////////////////////////////////////////
	///
	/// Components
	///
	///////////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	class UStaticMeshComponent* PianoBoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APS1Character* Interactor) override;
};
