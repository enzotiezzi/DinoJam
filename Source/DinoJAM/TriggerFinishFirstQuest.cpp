// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerFinishFirstQuest.h"

#include "DinoJAMGameModeBase.h"
#include "Level1InitialQuest.h"
#include "Level1Objectives.h"
#include "MyGameInstance.h"
#include "QuestSystem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerFinishFirstQuest::ATriggerFinishFirstQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);

	SkeletalMeshComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ATriggerFinishFirstQuest::BeginPlay()
{
	Super::BeginPlay();

	if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if(MyGameInstance->Level1Objectives)
		{
			MyGameInstance->Level1Objectives->KarenOutDoorStairs = this;
		}
	}
}

// Called every frame
void ATriggerFinishFirstQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerFinishFirstQuest::Interact(APS1Character* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1InitialQuest* InitialQuest = Cast<ULevel1InitialQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(InitialQuest)
			{
				InitialQuest->CompleteQuest(GetWorld());

				MyGameMode->ChangeLevel(FName("L_KarenIndoor"));
			}
		}
	}
}
