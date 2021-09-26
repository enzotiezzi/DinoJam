// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1SetupPianoQuest.h"

#include "TriggerPlacePianoBox.h"
#include "Kismet/GameplayStatics.h"

void ULevel1SetupPianoQuest::OnQuestStart(UWorld* World)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(DialogStartQuest, FOnDialogFinish());
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));

	if(MyGameInstance)
	{
		MyGameInstance->TriggerPlacePianoBox->SetActorHiddenInGame(false);
		MyGameInstance->TriggerPlacePianoBox->SetActorEnableCollision(true);
	}
}