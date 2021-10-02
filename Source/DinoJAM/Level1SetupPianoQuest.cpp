// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1SetupPianoQuest.h"

#include "PS1Character.h"
#include "TriggerPlacePianoBox.h"
#include "Kismet/GameplayStatics.h"

void ULevel1SetupPianoQuest::OnQuestStart(UWorld* World)
{
	StarterDialogFinish.BindUObject(this, &ULevel1SetupPianoQuest::OnStarterDialogFinish);
	
	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World));

	if(MyGameMode)
	{
		MyGameMode->StartDialogSystem(DialogStartQuest, StarterDialogFinish);
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(World));

	if(MyGameInstance)
	{
		MyGameInstance->TriggerPlacePianoBox->SetActorHiddenInGame(false);
		MyGameInstance->TriggerPlacePianoBox->SetActorEnableCollision(true);
	}
}

void ULevel1SetupPianoQuest::OnStarterDialogFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(DialogItem->World));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentNPC)
		{
			MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(DialogItem->NPCFaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);
		}
	}
}
