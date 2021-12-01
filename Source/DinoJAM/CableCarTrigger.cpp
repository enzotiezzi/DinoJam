// Fill out your copyright notice in the Description page of Project Settings.


#include "CableCarTrigger.h"

#include "Gear.h"
#include "InventorySystem.h"
#include "LevelSequencePlayer.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "RedKey.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACableCarTrigger::ACableCarTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(SphereComponent);
	SkeletalMeshComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ACableCarTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACableCarTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACableCarTrigger::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* Player = Cast<APlayerCharacter>(Interactor))
	{
		PlayerCharacter = Player;
		
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			const AItem* RedKey = MyGameInstance->InventorySystem->GetItem<ARedKey>();
			const AItem* Gear = MyGameInstance->InventorySystem->GetItem<AGear>();

			if(RedKey && Gear)
			{
				if(CableCarSequence)
				{
					FMovieSceneSequencePlaybackSettings MovieSceneSequencePlaybackSettings;
					MovieSceneSequencePlaybackSettings.bHidePlayer = true;
					MovieSceneSequencePlaybackSettings.bDisableMovementInput = true;
					MovieSceneSequencePlaybackSettings.bHideHud = true;

					ALevelSequenceActor* LevelSequenceActor;
					
					ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CableCarSequence, MovieSceneSequencePlaybackSettings, LevelSequenceActor);

					if(LevelSequencePlayer)
					{
						HideIndicator();
						
						LevelSequencePlayer->OnFinished.AddDynamic(this, &ACableCarTrigger::OnCableCarSequenceFinished);

						LevelSequencePlayer->Play();
					}
				}
			}
		}
	}
}

void ACableCarTrigger::OnCableCarSequenceFinished()
{
	if(CableCarExit)
	{
		PlayerCharacter->SetActorRelativeLocation(CableCarExit->GetActorLocation());
	}
}