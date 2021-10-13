#include "GateTrigger.h"

#include "DinoJAMGameModeBase.h"
#include "LevelSequenceActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Fill out your copyright notice in the Description page of Project Settings.

// Sets default values
AGateTrigger::AGateTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void AGateTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateTrigger::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ALevelSequenceActor* LevelSequenceActor;

		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MyGameMode->GateLevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

		if(LevelSequencePlayer)
		{
			LevelSequencePlayer->OnFinished.AddDynamic(this, &AGateTrigger::OnCutsceneFinished);
			
			LevelSequencePlayer->Play();
		}
	}
}

void AGateTrigger::OnCutsceneFinished()
{
}
