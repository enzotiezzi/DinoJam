// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog.h"

#include "Kismet/GameplayStatics.h"

UDialog::UDialog()
{
	OnDialogFinish.BindUObject(this, &UDialog::OnDialogFinished);
}

void UDialog::OnDialogFinished(class UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			if(bRestoreNPCState)
			{
				MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
				MyGameInstance->CurrentNPC->StopAnimMontage();
			}
		}

		if(MyGameInstance->CurrentPlayerCharacter)
		{
			if(bRestorePlayerState)
			{
				MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(MyGameInstance->CurrentPlayerCharacter->FaceMaterialIndex, MyGameInstance->CurrentPlayerCharacter->DefaultFaceExpression);
				MyGameInstance->CurrentPlayerCharacter->StopAnimMontage();
			}
		}
	}
}
