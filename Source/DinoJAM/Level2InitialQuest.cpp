// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2InitialQuest.h"

void ULevel2InitialQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

	OnStartingDialogFinish.BindUObject(this, &ULevel2InitialQuest::OnStartingDialogFinished);
}

void ULevel2InitialQuest::OnStartingDialogFinished(UDialogItem* DialogItem)
{
	
}
