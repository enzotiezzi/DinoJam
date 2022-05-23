// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2SetupGlassesQuest.h"

#include "DialogSystem.h"
#include "Kismet/GameplayStatics.h"
#include <DinoJAM/Cyclop.h>
#include "Blueprint/UserWidget.h"

void ULevel2SetupGlassesQuest::OnQuestStart(UWorld* World)
{
	Super::OnQuestStart(World);

	Cast<UDialog>(CharactersDialog[ACyclop::StaticClass()].GetDefaultObject())->OnDialogFinish.BindUObject(this, &ULevel2SetupGlassesQuest::OnMainDialogFinish);

	if(const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(World)))
	{
		MyGameMode->DialogSystem->StartDialogSystem(StartingDialog.GetDefaultObject());
	}
}

void ULevel2SetupGlassesQuest::OnMainDialogFinish(UDialogItem* DialogItem) 
{
	CompleteQuest(DialogItem->World);

	if (WidgetSignatureReference)
	{
		WidgetSignature = CreateWidget<UUserWidget>(DialogItem->World, WidgetSignatureReference);

		if (WidgetSignature) 
		{
			WidgetSignature->AddToViewport();

			FTimerHandle WidgetSignatureTimerHandle;

			DialogItem->World->GetTimerManager().SetTimer(WidgetSignatureTimerHandle, [this] ()
				{
					if (WidgetSignature && WidgetSignature->IsInViewport()) 
					{
						WidgetSignature->RemoveFromViewport();
					}
				}, RemoveSignatureWidgetInSeconds, false);

			ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(DialogItem->World));

			if (MyGameMode)
			{
				// change level
			}
		}
	}
}