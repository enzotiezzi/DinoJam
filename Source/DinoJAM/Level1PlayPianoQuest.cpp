// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1PlayPianoQuest.h"

#include "DialogSystem.h"
#include "Karen.h"
#include "Kismet/GameplayStatics.h"


void ULevel1PlayPianoQuest::OnQuestStart(UWorld* World)
{
	Cast<UDialog>(AfterPlayPianoDialog.GetDefaultObject())->OnDialogFinish.BindUObject(this, &ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish);
	
	CharactersDialog[AKaren::StaticClass()] = StartDialog;
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->DialogSystem->StartDialogSystem(StartDialog.GetDefaultObject());
	}
}

void ULevel1PlayPianoQuest::ExecuteDialogAfterPlayPianoFinish(UDialogItem* DialogItem)
{
	CompleteQuest(DialogItem->World);

	CharactersDialog[AKaren::StaticClass()] = AfterPlayPianoDialog;

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