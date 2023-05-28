// Fill out your copyright notice in the Description page of Project Settings.


#include "Level3WormBoxTriggerSphere.h"

#include "WormPack.h"
#include "Components/BillboardComponent.h"
#include "DinoJAM/InventorySystem.h"
#include "DinoJAM/MyGameInstance.h"
#include "DinoJAM/PianoBox.h"
#include "DinoJAM/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ALevel3WormBoxTriggerSphere::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		if(PlayerCharacter->bIsCarryPackageAnimation)
		{
			PlayerCharacter->Package->Destroy();
			PlayerCharacter->DropPackage();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				
			AWormBook* WormBook = GetWorld()->SpawnActor<AWormBook>(WormBookRef, GetSpriteComponent()->GetComponentLocation(), GetSpriteComponent()->GetComponentRotation(), SpawnParameters);
		}
	}
}

