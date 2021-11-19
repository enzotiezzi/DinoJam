// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "InventorySystem.h"
#include "QuestSystem.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::OnStart()
{
	InventorySystem = Cast<UInventorySystem>(InventorySystemReference.GetDefaultObject());
	QuestSystem = Cast<UQuestSystem>(QuestSystemReference.GetDefaultObject());
	
	if(InventorySystem)
	{
		InventorySystem->CurrentWorld = GetWorld();
		InventorySystem->SetupInventoryWidget(GetWorld());
		InventorySystem->SetupItemPopUpWidget(GetWorld());
	}

	if(QuestSystem)
	{
		QuestSystem->CurrentWorld = GetWorld();
		QuestSystem->StartQuest(QuestSystem->CurrentQuest.GetDefaultObject());
	}
}