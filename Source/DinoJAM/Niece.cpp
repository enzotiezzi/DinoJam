// Fill out your copyright notice in the Description page of Project Settings.


#include "Niece.h"

#include "DialogSystem.h"
#include "Level2InitialQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ANiece::ANiece()
{
}

void ANiece::Interact(APS1Character* Interactor)
{
	if(Cast<APlayerCharacter>(Interactor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(MyGameMode)
			{
				MyGameMode->DialogSystem->StartDialogSystem(MyGameInstance->QuestSystem->GetCurrentQuest()->GetDialog(GetClass()->GetSuperClass()).GetDefaultObject(), Cast<APlayerCharacter>(Interactor), this);
			}
		}
	}
}
