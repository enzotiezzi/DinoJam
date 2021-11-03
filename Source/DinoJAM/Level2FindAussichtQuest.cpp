// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2FindAussichtQuest.h"

#include "Kismet/GameplayStatics.h"

void ULevel2FindAussichtQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

	OnDialogFinish.BindUObject(this, &ULevel2FindAussichtQuest::OnStartDialogFinished);
	OnStartDialogFinish.BindUObject(this, &ULevel2FindAussichtQuest::OnStartDialogFinished);
}

void ULevel2FindAussichtQuest::OnStartDialogFinished(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
			MyGameInstance->CurrentNPC->StopAnimMontage();

			MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(MyGameInstance->CurrentPlayerCharacter->FaceMaterialIndex, MyGameInstance->CurrentPlayerCharacter->DefaultFaceExpression);
			MyGameInstance->CurrentPlayerCharacter->StopAnimMontage();
		}
	}
}
