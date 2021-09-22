// Fill out your copyright notice in the Description page of Project Settings.


#include "UQuest.h"

#include "Kismet/GameplayStatics.h"

UQuest::UQuest()
{
	bCompleted = false;
}

void UQuest::OnQuestFinish(UWorld* World)
{
	
}

void UQuest::OnQuestStart(UWorld* World)
{
	
}

void UQuest::CompleteQuest(UWorld* World)
{
	if(!bCompleted)
		bCompleted = true;
	
	if(NextQuest)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World);

		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

		if(MyGameMode)
		{
			UQuest* Quest = Cast<UQuest>(NextQuest->GetDefaultObject());
			
			MyGameMode->StartQuest(Quest);
		}
	}
}