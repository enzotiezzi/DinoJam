// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlaceMrAussichtPack.h"

#include "Cyclop.h"
#include "PianoBox.h"
#include "PlayerCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include <DinoJAM/MyGameInstance.h>
#include <DinoJAM/InventorySystem.h>

ATriggerPlaceMrAussichtPack::ATriggerPlaceMrAussichtPack()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow"));

	SetRootComponent(SphereComponent);
	SkeletalMeshComponent->SetupAttachment(SphereComponent);
	SpawnArrow->SetupAttachment(SphereComponent);

	SetActorEnableCollision(false);
}

void ATriggerPlaceMrAussichtPack::BeginPlay() 
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{
		MyGameInstance->Level2Objectives->PlaceMrAussichtPackObjective = this;
	}

	Super::BeginPlay();
}

void ATriggerPlaceMrAussichtPack::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		if(PlayerCharacter->bIsCarryPackageAnimation)
		{
			PlayerCharacter->Package->Destroy();
			PlayerCharacter->DropPackage();

			if(Glasses)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				
				AMrAussichtGlasses* MrAussichtGlasses = GetWorld()->SpawnActor<AMrAussichtGlasses>(Glasses, SpawnArrow->GetComponentLocation(), SpawnArrow->GetComponentRotation(), SpawnParameters);

				MrAussichtGlasses->ShowIndicator();
				
				HideIndicator();
				SetActorEnableCollision(false);
			}
		}
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{
		MyGameInstance->InventorySystem->RemoveItem<APianoBox>();
	}
}
