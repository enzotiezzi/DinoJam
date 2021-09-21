// Fill out your copyright notice in the Description page of Project Settings.


#include "UQuest.h"

#include "Kismet/GameplayStatics.h"

UQuest::UQuest()
{
	
}

void UQuest::OnQuestFinish()
{
	
}

void UQuest::OnQuestStart()
{
	
}

void UQuest::CompleteQuest()
{
	bCompleted = true;
	
	if(NextQuest)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

		if(MyGameMode)
		{
			UQuest* Quest = Cast<UQuest>(NextQuest);
			
			MyGameMode->StartQuest(Quest);
		}
	}
}