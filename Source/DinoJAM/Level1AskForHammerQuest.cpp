// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1AskForHammerQuest.h"

#include "PS1Character.h"
#include "Kismet/GameplayStatics.h"

void ULevel1AskForHammerQuest::OnQuestStart(UWorld* World)
{
	OnPreDialogFinish.BindUObject(this, &ULevel1AskForHammerQuest::ExecuteOnDialogFinish);
	OnDontHaveHammerDialogFinish.BindUObject(this, &ULevel1AskForHammerQuest::ExecuteOnDialogFinish);
	OnHaveHammerDialogFinish.BindUObject(this, &ULevel1AskForHammerQuest::ExecuteOnDialogFinish);
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(PreDialog, OnPreDialogFinish);
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
	
	return OnDontHaveHammerDialogFinish;
}

void ULevel1AskForHammerQuest::ExecuteOnDialogFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(DialogItem->NPCFaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
			MyGameInstance->CurrentNPC->StopAnimMontage();

			MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(3, MyGameInstance->CurrentPlayerCharacter->DefaultFaceExpression);
		}
	}
}
