// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLevel1StarterQuest.h"

#include "DinoJAMGameModeBase.h"
#include "Level1InitialQuest.h"
#include "Level1Objectives.h"
#include "MyGameInstance.h"
#include "Objective.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ATriggerLevel1StarterQuest::PreviewInteraction(APS1Character* Interactor)
{
	CurrentInteractor = Interactor;
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1InitialQuest* Quest = Cast<ULevel1InitialQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				Cast<UDialog>(Quest->CharactersDialog[Karen->GetClass()->GetSuperClass()].GetDefaultObject())->OnDialogFinish.BindUObject(this, &ATriggerLevel1StarterQuest::StopRotateToKaren);
				
				MyGameMode->DialogSystem->StartDialogSystem(Quest->GetDialog(Karen->GetClass()->GetSuperClass()).GetDefaultObject(), Cast<APlayerCharacter>(Interactor), Karen);

				this->SetActorEnableCollision(false);

				if(RotateToKarenTimerHandle.IsValid())
					GetWorld()->GetTimerManager().ClearTimer(RotateToKarenTimerHandle);
				
				GetWorld()->GetTimerManager().SetTimer(RotateToKarenTimerHandle, this, &ATriggerLevel1StarterQuest::OnRotateToKaren, GetWorld()->GetDeltaSeconds(), true);
			}
		}
	}
}

void ATriggerLevel1StarterQuest::OnRotateToKaren()
{
	const FRotator RotationToLookAt = UKismetMathLibrary::FindLookAtRotation(CurrentInteractor->GetActorLocation(), Karen->GetActorLocation());

	FRotator NewRotation = UKismetMathLibrary::RInterpTo(CurrentInteractor->GetActorRotation(), RotationToLookAt, GetWorld()->GetDeltaSeconds(), 5.0);
	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;
	
	CurrentInteractor->SetActorRelativeRotation(NewRotation);
}

void ATriggerLevel1StarterQuest::StopRotateToKaren(UDialogItem* DialogItem)
{
	GetWorld()->GetTimerManager().ClearTimer(RotateToKarenTimerHandle);

	if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGameInstance->Level1Objectives->KarenOutDoorStairs->ShowIndicator();
	}
}
