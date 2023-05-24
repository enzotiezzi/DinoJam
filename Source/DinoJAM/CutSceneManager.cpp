// Fill out your copyright notice in the Description page of Project Settings.

#include "CutSceneManager.h"
#include <DinoJAM/DinoJAMGameModeBase.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <LevelSequence/Public/LevelSequence.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

// Sets default values
ACutSceneManager::ACutSceneManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACutSceneManager::BeginPlay()
{
	Super::BeginPlay();

	if (ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->CutsceneManager = this;
	}
	
	if (Sequence)
	{
		ALevelSequenceActor* Actor;

		FMovieSceneSequencePlaybackSettings Settings;
		Settings.bDisableMovementInput = true;
		Settings.bPauseAtEnd = true;
		Settings.bHidePlayer = true;

		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, Settings, Actor);
	}
}

// Called every frame
void ACutSceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACutSceneManager::PlayCurrentSequence()
{
	if (SequencePlayer)
	{
		SequencePlayer->Play();
	}
}

void ACutSceneManager::SetOnSceneFinished(FOnMovieSceneSequencePlayerEvent OnSceneFinished)
{
	if (SequencePlayer)
	{
		SequencePlayer->OnFinished = OnSceneFinished;
	}
}

void ACutSceneManager::SetSequence(ULevelSequence* NewSequence)
{
	Sequence = NewSequence;

	ALevelSequenceActor* Actor;

	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bDisableMovementInput = true;
	Settings.bPauseAtEnd = true;
	Settings.bHidePlayer = true;

	if (SequencePlayer)
		SequencePlayer->Stop();

	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, Settings, Actor);
}