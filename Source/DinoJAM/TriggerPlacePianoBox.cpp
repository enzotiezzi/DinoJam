// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacePianoBox.h"

#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "Level1AskForHammerQuest.h"
#include "Level1Objectives.h"
#include "Level1SetupPianoQuest.h"
#include "MyGameInstance.h"
#include "PianoBox.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
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
	SkeletalMeshComponent->SetupAttachment(SphereComponent);
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
	
	MyGameInstance->Level1Objectives->KarenIndoorPlaceBox = this;
}

// Called every frame
void ATriggerPlacePianoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerPlacePianoBox::Interact(APS1Character* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameMode)
	{
		if(MyGameInstance)
		{
			ULevel1SetupPianoQuest* Quest = Cast<ULevel1SetupPianoQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);
		
				if(PlayerCharacter)
				{
					PianoBoxComponent->DestroyComponent();
					SkeletalMeshComponent->DestroyComponent();
					
					PlayerCharacter->Package->PianoBoxComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
					PlayerCharacter->Package->PianoBoxComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepWorldTransform);
					PlayerCharacter->Package->PianoBoxComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
					PlayerCharacter->Package->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					
					PlayerCharacter->DropPackage();

					UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->DropItemSound, GetActorLocation(), GetActorRotation());
				}

				Quest->CompleteQuest(GetWorld());
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

		ATriggerGetHammer* Hammer = Cast<ATriggerGetHammer>(MyGameInstance->InventorySystem->GetItem<ATriggerGetHammer>());
		
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

		ATriggerGetHammer* Hammer = Cast<ATriggerGetHammer>(MyGameInstance->InventorySystem->GetItem<ATriggerGetHammer>());
		
		if(Hammer)
			Hammer->bCanUse = false;
	}
}
