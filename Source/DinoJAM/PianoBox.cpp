// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoBox.h"

#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "Level1GetPianoQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APianoBox::APianoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PianoBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoBoxComponent"));

	PianoBoxComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APianoBox::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DelayUntilAddItem, this, &APianoBox::AddItemToInventory, 1);
}

// Called every frame
void APianoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APianoBox::Interact(APS1Character* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1GetPianoQuest* Quest = Cast<ULevel1GetPianoQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				Quest->CompleteQuest(GetWorld());
				
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);

				PlayerCharacter->CarryPackage(this);

				FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

				PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				PianoBoxComponent->AttachToComponent(PlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
			}
		}
	}
}

void APianoBox::UseItem()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		ULevel1GetPianoQuest* Quest = Cast<ULevel1GetPianoQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

		if(Quest)
		{
			Quest->CompleteQuest(GetWorld());

			MyGameInstance->CurrentPlayerCharacter->CarryPackage(this);

			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

			PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PianoBoxComponent->AttachToComponent(MyGameInstance->CurrentPlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
			
			MyGameInstance->InventorySystem->HideInventory();
		}
	}
}

void APianoBox::AddItemToInventory()
{
	GetWorld()->GetTimerManager().ClearTimer(DelayUntilAddItem);
	
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		MyGameInstance->InventorySystem->AddItem(this);
	}
}
