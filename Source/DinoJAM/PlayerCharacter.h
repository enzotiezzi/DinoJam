// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PS1Character.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DINOJAM_API APlayerCharacter : public APS1Character
{
	GENERATED_BODY()

protected:
	//////////////////////////////////////////////////
	///
	/// STEP SOUNDS
	/// 
	//////////////////////////////////////////////////
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayStepSound();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundAttenuation* StepSoundAttenuation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* ConcreteStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* WoodenStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* DirtStepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Step Sounds")
	class USoundCue* TiledStepSound;

	//////////////////////////////////////////////////
	///
	/// ANIMATION MONTAGES
	///
	//////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animations")
	class UAnimMontage* CarryPianoBoxMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animations")
	class UAnimMontage* WavingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animations")
	class UAnimMontage* BuildAnimation;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////////////////////////////////////////////////
	///
	/// INTERARCTIONS
	///
	////////////////////////////////////////////////////
	class IInteractable* CurrentInteractable;
	
	void Interact();

	///////////////////////////////////////////////////
	///
	/// MOVEMENT
	///
	///////////////////////////////////////////////////
	void MoveForward(float AxisValue);
	
	void MoveSides(float AxisValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite)
	float TurnSpeed = 1;

	////////////////////////////////////////////////////
	///
	/// INVENTORY 
	///
	////////////////////////////////////////////////////
	void PauseGame();

	void OpenInventory();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	////////////////////////////////////////////////////
	///
	/// FLAGS
	///
	///////////////////////////////////////////////////
	bool bIsOnDialog = false;
	
	bool bCanMove = true;

	bool bCanInteract = true;
	
	//////////////////////////////////////////////////////////////////
	///
	/// FUNCTIONS TO MANAGE DIALOG STATE
	/// 
	//////////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////////////////
	///
	/// PACKAGEG STUFF
	///
	/////////////////////////////////////////////////////////////////
	
	UPROPERTY(BlueprintReadWrite)
	class APianoBox* Package;
	
	void CarryPackage(class APianoBox* NewPackage)
	{
		Package = NewPackage;
		
		bIsCarryPackageAnimation = true;
		
		PlayAnimMontage(CarryPianoBoxMontage);
	}

	void DropPackage()
	{
		bIsCarryPackageAnimation = false;

		PlayAnimMontage(nullptr);
	}

	//////////////////////////////////////////////////////////////////
	///
	/// FUNCTIONS TO MANAGE COLLISIONS WITH INTERACTABLES
	/// 
	//////////////////////////////////////////////////////////////////
	UFUNCTION()
	void OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnCapsuleComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	////////////////////////////////////////////////////////
	///
	/// VARIABLES TO CONTROL THE ANIMATION BLENDS
	/// 
	////////////////////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Animation")
	bool bIsCarryPackageAnimation = false;

	bool bIsRootMotionAnimation = false;

	////////////////////////////////////////////////////////
	///
	/// START ANIMATIONS
	///
	////////////////////////////////////////////////////////
	void StartWavingAnimationMontage();

	void StartBuildAnimation();

	///////////////////////////////////////////////////////
	///
	/// MOVEMENT CONTROL
	///
	///////////////////////////////////////////////////////
	void StopMoving()
	{
		bCanMove = false;
	}

	void ContinueMoving()
	{
		bCanMove = true;
	}
};