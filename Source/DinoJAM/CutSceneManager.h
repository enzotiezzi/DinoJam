// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <LevelSequence/Public/LevelSequence.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include "CutSceneManager.generated.h"

UCLASS()
class DINOJAM_API ACutSceneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACutSceneManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayCurrentSequence();

	void SetOnSceneFinished(FOnMovieSceneSequencePlayerEvent OnSceneFinished);

	void SetSequence(ULevelSequence* NewSequence);
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULevelSequencePlayer* SequencePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelSequence* Sequence;
};
