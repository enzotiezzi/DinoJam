// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenKey.h"

#include "DinoJAMGameModeBase.h"
#include "GateTrigger.h"
#include "InventorySystem.h"
#include "LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"

AGoldenKey::AGoldenKey()
{
	bCanUse = false;
}

void AGoldenKey::UseItem()
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(MyGameMode)
	{
		if(MyGameInstance)
		{
			ALevelSequenceActor* LevelSequenceActor;
			FMovieSceneSequencePlaybackSettings MovieSceneSequencePlaybackSettings;
			MovieSceneSequencePlaybackSettings.bDisableMovementInput = true;

			ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MyGameMode->GateLevelSequence, MovieSceneSequencePlaybackSettings, LevelSequenceActor);

			if(LevelSequencePlayer)
			{
				if(GateTrigger)
					GateTrigger->Destroy();
				
				LevelSequencePlayer->Play();
			}
		}
	}
}
