// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1SetupPianoQuest.h"

#include "Kismet/GameplayStatics.h"

void ULevel1SetupPianoQuest::OnQuestStart()
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(DialogStartQuest, FOnDialogFinish());
	}
}