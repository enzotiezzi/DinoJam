//Copyright 1998-2021 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlendTriggerVolume.generated.h"

UCLASS()
class DINOJAM_API ABlendTriggerVolume : public AActor
{
	GENERATED_BODY()

	public:    
	// Sets default values for this actor's properties
	ABlendTriggerVolume();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* OverlapVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	ACameraActor* CameraToFind;

	UPROPERTY(EditDefaultsOnly, meta =(ClampMin = 0.0f), Category="Camera")
	float CameraBlendTime;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	virtual void NotifyActorEndOverlap(AActor* OtherActor);

	public:    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};