// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BookWorm.h"
#include "DinoJAM/Dialog.h"
#include "GameFramework/Actor.h"
#include "Level3Hallway1DialogInit.generated.h"

UCLASS()
class DINOJAM_API ALevel3Hallway1DialogInit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel3Hallway1DialogInit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	TSubclassOf<UDialog> StarterDialog;

	UFUNCTION(BlueprintCallable)
	void OnStarterDialogFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequence")
	ULevelSequence* WormIntroSequence;

	UFUNCTION(BlueprintCallable)
	void OnSequenceFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	TSubclassOf<UDialog> LastDialog;

	UFUNCTION(BlueprintCallable)
	void OnLastDialogFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objective")
	AObjective* Objective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worm")
	TSubclassOf<ABookWorm> BookWormRef;
};
