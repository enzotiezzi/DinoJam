// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2InitialQuest.h"


void ULevel2InitialQuest::OnQuestStart(UWorld* World)
{
	Cast<UDialog>(StartingDialog.GetDefaultObject())->OnDialogFinish.BindUObject(this, &ULevel2InitialQuest::OnStartingDialogFinish);
}

void ULevel2InitialQuest::OnStartingDialogFinish(UDialogItem* DialogItem)
{
	CompleteQuest(DialogItem->World);
}
