// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlayPiano.h"

#include "DinoJAMGameModeBase.h"
#include "Level1PlayPianoQuest.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ATriggerPlayPiano::ATriggerPlayPiano()
{
	PianoStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoStaticMeshComponent"));

	PianoStaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ATriggerPlayPiano::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1PlayPianoQuest* Quest = Cast<ULevel1PlayPianoQuest>(MyGameMode->qCurrentQuest);

		if(Quest)
		{
			if(!Quest->bCompleted)
			{
				if(Music)
				{
					MyGameMode->CurrentPlayerCharacter->StartDialog();
					
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), Music, GetActorLocation(), FRotator::ZeroRotator, 1, 1, 0, SoundAttenuation);

					GetWorld()->GetTimerManager().SetTimer(MusicTimerHandle, this, &ATriggerPlayPiano::OnMusicFinish, Music->Duration);
				}
			}
		}
	}
}

void ATriggerPlayPiano::OnMusicFinish()
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1PlayPianoQuest* Quest = Cast<ULevel1PlayPianoQuest>(MyGameMode->qCurrentQuest);

		if(Quest)
		{
			MyGameMode->StartDialogSystem(Quest->AfterPlayPianoDialog, Quest->OnDialogAfterPlayPianoFinish);
		}
	}
}