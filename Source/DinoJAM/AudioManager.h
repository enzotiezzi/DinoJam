// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class DINOJAM_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadwrite, Category = "Environment")
	UAudioComponent* EnvironmentAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Environment")
	TArray<UAudioComponent*> SoundsAudioComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Environment")
	USoundBase* EnvironmentSound;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Environment")
	TArray<USoundBase*> Sounds;
};
