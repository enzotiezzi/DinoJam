// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/VectorRegister.h"
#include "PlayerCharacterResizer.generated.h"

UCLASS()
class DINOJAM_API APlayerCharacterResizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCharacterResizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Size")
	FVector NewScale;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
