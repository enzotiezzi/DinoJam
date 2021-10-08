// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerGetHammer.h"

#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "Level1AskForHammerQuest.h"
#include "MyGameInstance.h"
#include "TriggerPlacePianoBox.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ATriggerGetHammer::BeginPlay()
{
	Super::BeginPlay();

	bCanUse = false;
}

ATriggerGetHammer::ATriggerGetHammer()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	StaticMeshComponent->SetupAttachment(GetRootComponent());
}


void ATriggerGetHammer::Interact(ACharacter* Interactor)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		ULevel1AskForHammerQuest* Quest = Cast<ULevel1AskForHammerQuest>(MyGameInstance->qCurrentQuest);

		if(Quest)
		{
			if(!Quest->bCompleted)
			{
				MyGameInstance->InventorySystem->AddItem(this);
				
				Quest->bHaveHammer = true;

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());

				Destroy();
			}
		}
	}
}

void ATriggerGetHammer::UseItem()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		ULevel1AskForHammerQuest* AskForHammerQuest = Cast<ULevel1AskForHammerQuest>(MyGameInstance->qCurrentQuest);

		if(AskForHammerQuest)
		{
			if(!AskForHammerQuest->bCompleted && AskForHammerQuest->bHaveHammer)
			{
				AskForHammerQuest->CompleteQuest(GetWorld());

				if(MyGameInstance->TriggerPlayPiano)
				{
					GetWorld()->SpawnActor<ATriggerPlayPiano>(MyGameInstance->TriggerPlayPiano, MyGameInstance->TriggerPlacePianoBox->GetActorLocation() + FVector(0, 0, 35), MyGameInstance->TriggerPlacePianoBox->GetActorRotation(), FActorSpawnParameters());

					Destroy();
					
					MyGameInstance->PianoBoxComponent->DestroyComponent();
				}
			}
		}
	}
}
