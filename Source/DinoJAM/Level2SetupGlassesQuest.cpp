// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2SetupGlassesQuest.h"

#include "DialogSystem.h"
#include "Kismet/GameplayStatics.h"

void ULevel2SetupGlassesQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

	if(const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World)))
	{
		MyGameMode->DialogSystem->StartDialogSystem(StartingDialog.GetDefaultObject());
	}
}
