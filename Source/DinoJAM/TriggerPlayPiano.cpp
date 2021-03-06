// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlayPiano.h"

#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "Level1PlayPianoQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ATriggerPlayPiano::ATriggerPlayPiano()
{
	PianoStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoStaticMeshComponent"));

	PianoStaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ATriggerPlayPiano::Interact(APS1Character* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1PlayPianoQuest* Quest = Cast<ULevel1PlayPianoQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				if(Music)
				{
					MyGameInstance->CurrentPlayerCharacter->StartDialog();
					MyGameInstance->CurrentPlayerCharacter->StartBuildAnimation();
				
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
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1PlayPianoQuest* Quest = Cast<ULevel1PlayPianoQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				MyGameInstance->CurrentPlayerCharacter->StopAnimMontage();
				
				MyGameMode->DialogSystem->StartDialogSystem(Quest->AfterPlayPianoDialog.GetDefaultObject());
			}
		}
	}
}