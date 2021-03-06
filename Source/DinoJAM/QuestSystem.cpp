// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystem.h"

#include "UQuest.h"

UQuestSystem::UQuestSystem()
{
	
}

void UQuestSystem::StartQuest(UQuest* Quest)
{
	if (qCurrentQuest)
		qCurrentQuest->OnQuestFinish(CurrentWorld);

	qCurrentQuest = Quest;

	qCurrentQuest->OnQuestStart(CurrentWorld);
}