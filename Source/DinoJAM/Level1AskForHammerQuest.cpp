// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1AskForHammerQuest.h"

#include "DialogSystem.h"
#include "PS1Character.h"
#include "Kismet/GameplayStatics.h"

void ULevel1AskForHammerQuest::OnQuestStart(UWorld* World)
{
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->DialogSystem->StartDialogSystem(PreDialog.GetDefaultObject());
	}
}

TSubclassOf<UDialog> ULevel1AskForHammerQuest::GetDialog(UClass* Class)
{
	if(bHaveHammer)
		return HaveHammerDialog;

	return DontHaveHammerDialog;
}


void ULevel1AskForHammerQuest::ExecuteOnDialogFinish(UDialogItem* DialogItem)
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
