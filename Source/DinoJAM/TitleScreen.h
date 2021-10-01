// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TitleScreen.generated.h"

UCLASS()
class DINOJAM_API ATitleScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATitleScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
