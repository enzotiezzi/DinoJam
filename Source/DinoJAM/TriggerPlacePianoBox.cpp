// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacePianoBox.h"

#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "Level1AskForHammerQuest.h"
#include "Level1SetupPianoQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "TriggerGetHammer.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ATriggerPlacePianoBox::ATriggerPlacePianoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	PianoBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoBoxComponent"));

	SetRootComponent(SphereComponent);
	PianoBoxComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ATriggerPlacePianoBox::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		MyGameInstance->TriggerPlacePianoBox = this;
	}
}

// Called every frame
void ATriggerPlacePianoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerPlacePianoBox::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameMode)
	{
		if(MyGameInstance)
		{
			ULevel1SetupPianoQuest* Quest = Cast<ULevel1SetupPianoQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				if(!Quest->bCompleted)
				{
					APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);
			
					if(PlayerCharacter)
					{
						PianoBoxComponent->DestroyComponent();
						
						MyGameInstance->PianoBoxComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
						MyGameInstance->PianoBoxComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepWorldTransform);
						MyGameInstance->PianoBoxComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
						MyGameInstance->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
						
						PlayerCharacter->DropPianoBox();

						UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->DropItemSound, GetActorLocation(), GetActorRotation());
					}

					Quest->CompleteQuest(GetWorld());
				}
			}
		}
	}
}

void ATriggerPlacePianoBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		// CAN USE HAMMER
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		ATriggerGetHammer* Hammer = Cast<ATriggerGetHammer>(MyGameInstance->InventorySystem->GetItem(0));
		
		if(Hammer)
			Hammer->bCanUse = true;
	}
}

void ATriggerPlacePianoBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		// CAN USE HAMMER
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		ATriggerGetHammer* Hammer = Cast<ATriggerGetHammer>(MyGameInstance->InventorySystem->GetItem(0));
		
		if(Hammer)
			Hammer->bCanUse = false;
	}
}
