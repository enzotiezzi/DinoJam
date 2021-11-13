// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerLevel2FindMrAussicht.generated.h"

UCLASS()
class DINOJAM_API ATriggerLevel2FindMrAussicht : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerLevel2FindMrAussicht();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mr Aussicht")
	class ACyclop* Cyclop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequence")
	class ULevelSequence* Sequence;

	bool bAlreadyPlayedSequence = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
