// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1GetPianoQuest.h"

#include "PS1Character.h"
#include "Kismet/GameplayStatics.h"

void ULevel1GetPianoQuest::OnQuestStart(UWorld* World)
{
	OnDialogFinish.BindUObject(this, &ULevel1GetPianoQuest::ExecuteOnDialogFinish);
}

void ULevel1GetPianoQuest::ExecuteOnDialogFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
			MyGameInstance->CurrentNPC->StopAnimMontage();
		}
	}
}