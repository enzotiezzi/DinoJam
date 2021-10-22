// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1PlayPianoQuest.h"

#include "Kismet/GameplayStatics.h"


void ULevel1PlayPianoQuest::OnQuestStart(UWorld* World)
{
	OnStarterDialogFinish.BindUObject(this, &ULevel1PlayPianoQuest::ExecuteOnStarterDialogFinish);
	OnDialogAfterPlayPianoFinish.BindUObject(this, &ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish);
	OnDialogFinish.BindUObject(this, &ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish);
	
	Dialog = StartDialog;
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(StartDialog, OnStarterDialogFinish);
	}
}

void ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish(UDialogItem* DialogItem)
{
	CompleteQuest(DialogItem->World);

	Dialog = AfterPlayPianoDialog;

	ExecuteOnStarterDialogFinish(DialogItem);
}

void ULevel1PlayPianoQuest::ExecuteOnStarterDialogFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
			MyGameInstance->CurrentNPC->StopAnimMontage();

			MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(MyGameInstance->CurrentPlayerCharacter->FaceMaterialIndex, MyGameInstance->CurrentPlayerCharacter->DefaultFaceExpression);
		}
	}
}