// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DINOJAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// STEP SOUNDS
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* ConcreteStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* WoodenStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* DirtStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* TiledStepSound;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact();


	void MoveForward(float AxisValue);
	
	void MoveSides(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayStepSound();

	bool bIsOnDialog = false;
	
	bool bCanMove = true;

	class IInteractable* CurrentInteractable;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDialogFinish()
	{
		bCanMove = true;
		bIsOnDialog = false;
	}

	void StartDialog()
	{
		bCanMove = false;
		bIsOnDialog = true;
	}

	UFUNCTION()
	void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnCapsuleComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
