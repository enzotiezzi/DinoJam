// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DINOJAM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// STEP SOUNDS
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundBase* ConcreteStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundBase* WoodenStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundBase* DirtStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundBase* TiledStepSound;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UArrowComponent* StepArrowComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact();

	bool bIsOnDialog = true;

	void MoveForward(float AxisValue);
	
	void MoveSides(float AxisValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayStepSound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDialogFinish();
};
