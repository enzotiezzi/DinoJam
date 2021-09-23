// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerGetHammer.h"

#include "DinoJAMGameModeBase.h"
#include "Level1AskForHammerQuest.h"
#include "Kismet/GameplayStatics.h"

void ATriggerGetHammer::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1AskForHammerQuest* Quest = Cast<ULevel1AskForHammerQuest>(MyGameMode->qCurrentQuest);

		if(Quest)
		{
			if(!Quest->bCompleted)
				Quest->bHaveHammer = true;
		}
	}
}
