// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacePianoBox.h"

#include "DinoJAMGameModeBase.h"
#include "Level1SetupPianoQuest.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerPlacePianoBox::ATriggerPlacePianoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
}

// Called when the game starts or when spawned
void ATriggerPlacePianoBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerPlacePianoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerPlacePianoBox::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1SetupPianoQuest* Quest = Cast<ULevel1SetupPianoQuest>(MyGameMode->qCurrentQuest);

		if(Quest)
		{
			if(!Quest->bCompleted)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);
			
				if(PlayerCharacter)
				{
					MyGameMode->PianoBoxComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
					MyGameMode->PianoBoxComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepWorldTransform);
					MyGameMode->PianoBoxComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
					MyGameMode->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					
					PlayerCharacter->bIsCarryBoxAnimation = false;
				}

				Quest->CompleteQuest(GetWorld());
			}
		}
	}
}
