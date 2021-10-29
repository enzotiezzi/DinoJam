// Fill out your copyright notice in the Description page of Project Settings.


#include "Niece.h"

#include "Level2InitialQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ANiece::ANiece()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SphereComponent->SetupAttachment(GetRootComponent());
}

void ANiece::Interact(APS1Character* Interactor)
{
	if(Cast<APlayerCharacter>(Interactor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel2InitialQuest* Quest = Cast<ULevel2InitialQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

				if(MyGameMode)
				{
					MyGameMode->StartDialogSystem(Quest->Dialog, Quest->OnDialogFinish, Cast<APlayerCharacter>(Interactor), this);
				}
			}
		}
	}
}
