// Fill out your copyright notice in the Description page of Project Settings.


#include "UQuest.h"

#include "QuestSystem.h"
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
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));

			if(MyGameInstance)
			{
				UQuest* Quest = Cast<UQuest>(NextQuest->GetDefaultObject());
			
				MyGameInstance->QuestSystem->StartQuest(Quest);
			}
		}
	}
}

