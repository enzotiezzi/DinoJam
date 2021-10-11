
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "GateTrigger.generated.h"

UCLASS()
class DINOJAM_API AGateTrigger : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGateTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gates")
	class AActor* Gate1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gates")
	class AActor* Gate2;

	UFUNCTION()
	void OnCutsceneFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ACharacter* Interactor) override;
};
