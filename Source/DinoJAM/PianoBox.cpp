// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoBox.h"

#include "DinoJAMGameModeBase.h"
#include "Level1GetPianoQuest.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APianoBox::APianoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	PianoBoxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PianoBoxComponent"));

	SetRootComponent(SphereComponent);
	PianoBoxComponent->SetupAttachment(SphereComponent);

	SphereComponent->SetSphereRadius(64.0);
}

// Called when the game starts or when spawned
void APianoBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APianoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APianoBox::Interact(ACharacter* Interactor)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		ULevel1GetPianoQuest* Quest = Cast<ULevel1GetPianoQuest>(MyGameMode->qCurrentQuest);

		if(Quest)
		{
			if(!Quest->bCompleted)
			{
				Quest->CompleteQuest(GetWorld());

				MyGameMode->PianoBoxComponent = PianoBoxComponent;

				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor);
	
				PlayerCharacter->bIsCarryBoxAnimation = true;
	
				FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

				PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				PianoBoxComponent->AttachToComponent(PlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));
			}
		}
	}
}
