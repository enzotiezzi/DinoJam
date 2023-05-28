// Fill out your copyright notice in the Description page of Project Settings.


#include "Level3DoorTrigger.h"

#include "DinoJAM/DinoJAMGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ALevel3DoorTrigger::Interact(APS1Character* Interactor)
{
	if(ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		MyGameMode->ChangeLevel(FName("Hallway1"));
	}
}
