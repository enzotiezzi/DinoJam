// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLevel1StarterQuest.h"

#include "DinoJAMGameModeBase.h"
#include "Level1InitialQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ATriggerLevel1StarterQuest::PreviewInteraction(ACharacter* Interactor)
{
	CurrentInteractor = Interactor;
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel1InitialQuest* Quest = Cast<ULevel1InitialQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				MyGameMode->StartDialogSystem(Quest->Dialog, Quest->OnDialogFinish, Cast<APlayerCharacter>(Interactor), Karen);

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
	
	if (NewRotation.Yaw < .1 && NewRotation.Yaw > -.1)
		GetWorld()->GetTimerManager().ClearTimer(RotateToKarenTimerHandle);

	CurrentInteractor->SetActorRelativeRotation(NewRotation);
}
