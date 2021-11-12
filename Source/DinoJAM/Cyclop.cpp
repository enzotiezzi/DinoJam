// Fill out your copyright notice in the Description page of Project Settings.


#include "Cyclop.h"

#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

ACyclop::ACyclop()
{
	
}

void ACyclop::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(MyGameMode)
			{
				MyGameMode->DialogSystem->StartDialogSystem(MyGameInstance->qCurrentQuest->GetDialog(GetClass()->GetSuperClass()).GetDefaultObject(), PlayerCharacter, this);
			}
		}
	}
}
