// Fill out your copyright notice in the Description page of Project Settings.


#include "MoscaMansionOnFinishSequencer.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <DinoJAM/CutSceneManager.h>
#include <DinoJAM/DinoJAMGameModeBase.h>

// Sets default values
AMoscaMansionOnFinishSequencer::AMoscaMansionOnFinishSequencer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMoscaMansionOnFinishSequencer::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle BindOnSceneFinishTimer;
	GetWorld()->GetTimerManager().SetTimer(BindOnSceneFinishTimer, [this]()
		{
			if (ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				FOnMovieSceneSequencePlayerEvent OnFinish;
				OnFinish.AddDynamic(this, &AMoscaMansionOnFinishSequencer::OnSceneFinish);

				MyGameMode->CutsceneManager->SetOnSceneFinished(OnFinish);
				MyGameMode->CutsceneManager->PlayCurrentSequence();
			}
		}, .2, false);
}

// Called every frame
void AMoscaMansionOnFinishSequencer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoscaMansionOnFinishSequencer::OnSceneFinish()
{
	// TODO PROGRAM WHEN SCENE FINISHES

	GEngine->AddOnScreenDebugMessage(rand(), 1, FColor::Red, "Scene Finished");
}