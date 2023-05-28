// Fill out your copyright notice in the Description page of Project Settings.


#include "DrMosca.h"

#include "DinoJAM/DialogSystem.h"
#include "DinoJAM/DinoJAMGameModeBase.h"
#include "DinoJAM/PlayerCharacter.h"
#include "DinoJAM/QuestSystem.h"
#include "DinoJAM/UQuest.h"
#include "Kismet/GameplayStatics.h"

void ADrMosca::Interact(APS1Character* Interactor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(Interactor);
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			MyGameMode->DialogSystem->StartDialogSystem(MyGameInstance->QuestSystem->GetCurrentQuest()->GetDialog(GetClass()->GetSuperClass()).GetDefaultObject(), Player, this);
		}
	}
}
