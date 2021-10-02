// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PS1Character.generated.h"

UCLASS()
class DINOJAM_API APS1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APS1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Facial Expression")
	class UMaterialInterface* DefaultFaceExpression;
};
