// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "InventorySystem.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::OnStart()
{
	StartQuest(CurrentQuest.GetDefaultObject());

	InventorySystem = Cast<UInventorySystem>(InventorySystemReference.GetDefaultObject());

	if(InventorySystem)
	{
		InventorySystem->SetupInventoryWidget(GetWorld());
		InventorySystem->SetupItemPopUpWidget(GetWorld());
	}
}

void UMyGameInstance::StartQuest(UQuest* Quest)
{
	if (qCurrentQuest)
		qCurrentQuest->OnQuestFinish(GetWorld());

	qCurrentQuest = Quest;

	qCurrentQuest->OnQuestStart(GetWorld());
}