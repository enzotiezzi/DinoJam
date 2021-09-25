// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerGetHammer.h"

#include "DinoJAMGameModeBase.h"
#include "Level1AskForHammerQuest.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ATriggerGetHammer::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1AskForHammerQuest* Quest = Cast<ULevel1AskForHammerQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				if(!Quest->bCompleted)
				{
					Quest->bHaveHammer = true;

					UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
				}
			}
		}
	}
}
