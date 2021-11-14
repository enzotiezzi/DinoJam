#include "GateTrigger.h"

#include "DinoJAMGameModeBase.h"
#include "GoldenKey.h"
#include "InventorySystem.h"
#include "LevelSequenceActor.h"
#include "MrAussichtPack.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Fill out your copyright notice in the Description page of Project Settings.

// Sets default values
AGateTrigger::AGateTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void AGateTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateTrigger::OnCutsceneFinished()
{
}

void AGateTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(AItem* GoldenKey = MyGameInstance->InventorySystem->GetItem<AGoldenKey>())
		{
			GoldenKey->bCanUse = true;
		}
	}
}

void AGateTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(AItem* GoldenKey = MyGameInstance->InventorySystem->GetItem<AGoldenKey>())
		{
			GoldenKey->bCanUse = false;
		}
	}
}
