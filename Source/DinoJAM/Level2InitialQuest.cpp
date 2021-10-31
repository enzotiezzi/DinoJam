// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2InitialQuest.h"

#include "Kismet/GameplayStatics.h"

void ULevel2InitialQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

	OnStartingDialogFinish.BindUObject(this, &ULevel2InitialQuest::OnStartingDialogFinished);
	OnDialogFinish.BindUObject(this, &ULevel2InitialQuest::OnStartingDialogFinished);
}

void ULevel2InitialQuest::OnStartingDialogFinished(UDialogItem* DialogItem)
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
