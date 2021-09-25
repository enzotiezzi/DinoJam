// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLevel1StarterQuest.h"

#include "DinoJAMGameModeBase.h"
#include "Level1InitialQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATriggerLevel1StarterQuest::PreviewInteraction(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1InitialQuest* Quest = Cast<ULevel1InitialQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				MyGameMode->StartDialogSystem(Quest->Dialog, Quest->OnDialogFinish, Cast<APlayerCharacter>(Interactor), Karen);

				this->SetActorEnableCollision(false);
			}
		}
	}
}