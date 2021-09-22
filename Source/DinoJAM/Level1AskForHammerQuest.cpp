// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1AskForHammerQuest.h"

#include "Kismet/GameplayStatics.h"

void ULevel1AskForHammerQuest::OnQuestStart(UWorld* World)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(PreDialog, FOnDialogFinish());
	}
}

TArray<TSubclassOf<UDialogItem>> ULevel1AskForHammerQuest::GetDialogBasedOnComplexCondition()
{
	if(bHaveHammer)
		return HaveHammerDialog;
	
	return DontHaveHammerDialog;
}

FOnDialogFinish ULevel1AskForHammerQuest::GetOnDialogFinishBasedOnComplexCondition()
{
	if(bHaveHammer)
		return OnHaveHammerDialogFinish;
	
	return FOnDialogFinish();
}
