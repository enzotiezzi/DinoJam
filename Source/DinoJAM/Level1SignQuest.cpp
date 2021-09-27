// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1SignQuest.h"

void ULevel1SignQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

}

void ULevel1SignQuest::OnDialogFinish()
{
	CompleteQuest();
}
