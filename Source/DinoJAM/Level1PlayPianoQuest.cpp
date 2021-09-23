// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1PlayPianoQuest.h"

#include "Kismet/GameplayStatics.h"


void ULevel1PlayPianoQuest::OnQuestStart(UWorld* World)
{
	OnDialogAfterPlayPianoFinish.BindUObject(this, &ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish);

	Dialog = StartDialog;
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(StartDialog, FOnDialogFinish());
	}
}

void ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish(UDialogItem* DialogItem)
{
	CompleteQuest(DialogItem->World);

	Dialog = AfterPlayPianoDialog;
}