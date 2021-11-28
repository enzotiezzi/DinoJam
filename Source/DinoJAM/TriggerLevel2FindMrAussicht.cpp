// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLevel2FindMrAussicht.h"

#include "Cyclop.h"
#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "Item.h"
#include "Level2FindAussichtQuest.h"
#include "LevelSequencePlayer.h"
#include "MrAussichtPack.h"
#include "MyGameInstance.h"
#include "QuestSystem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerLevel2FindMrAussicht::ATriggerLevel2FindMrAussicht()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void ATriggerLevel2FindMrAussicht::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerLevel2FindMrAussicht::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerLevel2FindMrAussicht::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(!bAlreadyPlayedSequence)
	{
		if(Cast<APlayerCharacter>(OtherActor))
		{
			Player = OtherActor;
		
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			
			if(Sequence)
			{
				ALevelSequenceActor* LevelSequenceActor;

				FMovieSceneSequencePlaybackSettings MovieSceneSequencePlaybackSettings;
				MovieSceneSequencePlaybackSettings.bDisableMovementInput = true;
				MovieSceneSequencePlaybackSettings.bHideHud = true;
		
				ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, MovieSceneSequencePlaybackSettings, LevelSequenceActor);

				if(LevelSequencePlayer)
				{
					LevelSequencePlayer->OnFinished.AddDynamic(this, &ATriggerLevel2FindMrAussicht::OnSceneFinished);

					LevelSequencePlayer->Play();

					bAlreadyPlayedSequence = true;
				}

				if(MyGameInstance)
				{
					if(AItem* Item = MyGameInstance->InventorySystem->GetItem<AMrAussichtPack>())
					{
						Item->bCanUse = true;
					}
				}
			}
		}
	}
}

void ATriggerLevel2FindMrAussicht::NotifyActorEndOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			if(AItem* Item = MyGameInstance->InventorySystem->GetItem<AMrAussichtPack>())
			{
				Item->bCanUse = false;
			}
		}	
	}
}

void ATriggerLevel2FindMrAussicht::OnSceneFinished()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(Cyclop)
	{
		Cyclop->SetActorHiddenInGame(false);
		
		if(MyGameInstance)
		{
			ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if(MyGameMode)
			{
				ULevel2FindAussichtQuest* Quest = Cast<ULevel2FindAussichtQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

				if(Quest)
				{
					MyGameMode->DialogSystem->StartDialogSystem(Quest->StartQuestDialog.GetDefaultObject(), Cast<APlayerCharacter>(Player), Cyclop);
				}
			}
		}
	}
}