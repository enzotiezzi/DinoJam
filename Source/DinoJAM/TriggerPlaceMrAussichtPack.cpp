// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlaceMrAussichtPack.h"

#include "InventorySystem.h"
#include "Item.h"
#include "MrAussichtPack.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ATriggerPlaceMrAussichtPack::ATriggerPlaceMrAussichtPack()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
	SkeletalMeshComponent->SetupAttachment(SphereComponent);
}

void ATriggerPlaceMrAussichtPack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			if(AItem* Item = MyGameInstance->InventorySystem->GetItem<AMrAussichtPack>())
			{
				Item->bCanUse = true;
			}
		}
	}
}

void ATriggerPlaceMrAussichtPack::NotifyActorEndOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			if(AItem* Item = MyGameInstance->InventorySystem->GetItem<AMrAussichtPack>())
			{
				Item->bCanUse = false;
			}
		}
	}
}

void ATriggerPlaceMrAussichtPack::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		if(PlayerCharacter->bIsCarryBoxAnimation)
		{
			
		}
	}
}
