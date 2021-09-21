// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "Interactable.h"
#include "GameFramework/Character.h"
#include "Karen.generated.h"

UCLASS()
class DINOJAM_API AKaren : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKaren();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Interact(APlayerCharacter* Interactor) override;

	void UpdateDialogAnimationOwner(TArray<TSubclassOf<UDialogItem>> Dialog, APlayerCharacter* Interactor);
	
	//
	UPROPERTY()
	class APlayerCharacter* CurrentInteractor;
};
