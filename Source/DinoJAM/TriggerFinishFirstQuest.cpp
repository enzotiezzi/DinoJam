// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerFinishFirstQuest.h"

#include "DinoJAMGameModeBase.h"
#include "Level1InitialQuest.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerFinishFirstQuest::ATriggerFinishFirstQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void ATriggerFinishFirstQuest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerFinishFirstQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerFinishFirstQuest::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1InitialQuest* InitialQuest = Cast<ULevel1InitialQuest>(MyGameMode->qCurrentQuest);

		if(InitialQuest)
		{
			if(!InitialQuest->bCompleted)
			{
				InitialQuest->CompleteQuest(GetWorld());
			}
		}
	}
}
