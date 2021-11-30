// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1SignQuest.h"

#include "Karen.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ULevel1SignQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);
	Cast<UDialog>(CharactersDialog[AKaren::StaticClass()].GetDefaultObject())->OnDialogFinish.BindUObject(this, &ULevel1SignQuest::OnDialogFinish);
}

void ULevel1SignQuest::OnDialogFinish(UDialogItem* DialogItem)
{
	CompleteQuest(DialogItem->World);

	if(WidgetSignatureReference)
	{
		WidgetSignature = CreateWidget<UUserWidget>(DialogItem->World, WidgetSignatureReference);

		if(WidgetSignature)
		{
			WidgetSignature->AddToViewport();
			
			FTimerHandle HideSignatureTimerHandle;

			DialogItem->World->GetTimerManager().SetTimer(HideSignatureTimerHandle, [this, DialogItem]()
			{
				if(WidgetSignature)
				{
					if(WidgetSignature->IsInViewport())
					{
						WidgetSignature->RemoveFromViewport();
					}
				}
			}, RemoveSignatureWidgetInSeconds, false);
			
			CompleteQuest(DialogItem->World);

			ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(DialogItem->World));

			if(MyGameMode)
			{
				MyGameMode->ChangeLevel(FName("Cyclops_Level"));
			}
		}
	}
}
