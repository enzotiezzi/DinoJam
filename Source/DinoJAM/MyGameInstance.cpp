// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::OnStart()
{
	StartQuest(CurrentQuest.GetDefaultObject());
}

void UMyGameInstance::StartQuest(UQuest* Quest)
{
	if (qCurrentQuest)
		qCurrentQuest->OnQuestFinish(GetWorld());

	qCurrentQuest = Quest;

	qCurrentQuest->OnQuestStart(GetWorld());
}