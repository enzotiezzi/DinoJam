// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "InventorySystem.h"
#include "QuestSystem.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::OnStart()
{
	Level1Objectives = NewObject<ULevel1Objectives>();
	Level2Objectives = NewObject<ULevel2Objectives>();

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

	GetWorld()->GetTimerManager().SetTimer(GameInstanceTimerHandle, this, &UMyGameInstance::GameInstanceTick, GetWorld()->GetDeltaSeconds(), true);
}

void UMyGameInstance::GameInstanceTick() 
{
	FString CurrentQuestName = Cast<UQuest>(QuestSystem->CurrentQuest.GetDefaultObject())->Name;

	GEngine->AddOnScreenDebugMessage(rand(), .1, FColor::Red, "CurrentQuest - " + CurrentQuestName);
}