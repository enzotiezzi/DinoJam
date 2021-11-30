// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Level1DialogSystemInitializer.generated.h"

UCLASS()
class DINOJAM_API ALevel1DialogSystemInitializer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel1DialogSystemInitializer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AKaren* Karen;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
