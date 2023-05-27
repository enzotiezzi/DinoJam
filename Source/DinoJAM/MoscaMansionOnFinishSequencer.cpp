// Fill out your copyright notice in the Description page of Project Settings.


#include "MoscaMansionOnFinishSequencer.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <DinoJAM/CutSceneManager.h>
#include <DinoJAM/DinoJAMGameModeBase.h>

#include "DialogSystem.h"

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
	if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->CutsceneManager->SequencePlayer->Stop();
		
		if(DialogRef)
		{
			UDialog* Dialog = DialogRef.GetDefaultObject();
			Dialog->OnDialogFinish.BindUFunction(this, "OnDialogFinish");

			MyGameMode->DialogSystem->StartDialogSystem(Dialog);
		}
	}
}

void AMoscaMansionOnFinishSequencer::OnDialogFinish()
{
	if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(LastSequence)
		{
			FOnMovieSceneSequencePlayerEvent OnFinish;
			OnFinish.AddDynamic(this, &AMoscaMansionOnFinishSequencer::OnLastSequenceFinish);
			
			MyGameMode->CutsceneManager->SetSequence(LastSequence);
			MyGameMode->CutsceneManager->SetOnSceneFinished(OnFinish);
			MyGameMode->CutsceneManager->PlayCurrentSequence();
		}
	}
}

void AMoscaMansionOnFinishSequencer::OnLastSequenceFinish()
{
	if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->CutsceneManager->SequencePlayer->Stop();
	}
}
