// Fill out your copyright notice in the Description page of Project Settings.


#include "MrAussichtPack.h"

#include "Cyclop.h"
#include "DialogSystem.h"
#include "InventorySystem.h"
#include "Level2FindAussichtQuest.h"
#include "MyGameInstance.h"
#include "PianoBox.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include <DinoJAM/Objective.h>

AMrAussichtPack::AMrAussichtPack()
{
	bCanUse = false;
}

void AMrAussichtPack::BeginPlay()
{
	Super::BeginPlay();

	if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGameInstance->InventorySystem->AddItem(this);
	}
}

void AMrAussichtPack::UseItem()
{
	if (bCanUse)
	{
		if (BoxReference)
		{
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (MyGameInstance)
			{
				APianoBox* Box = GetWorld()->SpawnActor<APianoBox>(BoxReference, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());

				MyGameInstance->CurrentPlayerCharacter->CarryPackage(Box);

				const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

				Box->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->PianoBoxComponent->AttachToComponent(MyGameInstance->CurrentPlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());

				if (ULevel2FindAussichtQuest* Quest = Cast<ULevel2FindAussichtQuest>(MyGameInstance->QuestSystem->GetCurrentQuest()))
				{
					Quest->CompleteQuest(GetWorld());
				}

				if (MyGameInstance->Level2Objectives && MyGameInstance->Level2Objectives->PlaceMrAussichtPackObjective)
				{
					MyGameInstance->Level2Objectives->PlaceMrAussichtPackObjective->SetActorEnableCollision(true);
					MyGameInstance->Level2Objectives->PlaceMrAussichtPackObjective->ShowIndicator();
				}
			}
		}
	}
}
