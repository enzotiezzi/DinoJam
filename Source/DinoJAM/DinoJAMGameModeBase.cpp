// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

#include "PlayerCharacter.h"
#include "UQuest.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ADinoJAMGameModeBase::BeginPlay()
{
	if(WidgetDialogTextReference)
	{
		WidgetDialogText = CreateWidget<UUserWidget>(GetWorld(), WidgetDialogTextReference);

		if(WidgetDialogText)
		{
			WidgetDialogTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_Dialog"));
		}
	}

	StartQuest(CurrentQuest.GetDefaultObject());
}

void ADinoJAMGameModeBase::StartDialogSystem(TArray<TSubclassOf<UDialogItem>> NewDialogs, FOnDialogFinish OnNewDialogFinish)
{
	this->Dialogs = NewDialogs;
	this->OnDialogFinish = OnNewDialogFinish;

	if(Dialogs.Num() > 0)
	{
		UDialogItem* DialogItem = Dialogs[0].GetDefaultObject();
		Dialogs.RemoveAt(0);

		PlayDialog(DialogItem);
	}
}

void ADinoJAMGameModeBase::PlayDialog(UDialogItem* DialogItem)
{
	if(DialogItem)
	{
		if(DialogAudioComponent != nullptr)
			DialogAudioComponent->Stop();
	
		CurrentDialogItem = DialogItem;

		if(CurrentDialogSoundTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

		if(DelayToNextDialogTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
		if(DialogItem->Sound)
		{
			GetWorld()->GetTimerManager().SetTimer(CurrentDialogSoundTimerHandle, this, &ADinoJAMGameModeBase::OnDialogSoundFinish, DialogItem->Sound->Duration);

			DialogAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogItem->Sound);
		}

		if(!WidgetDialogText->IsInViewport())
			WidgetDialogText->AddToViewport();

		WidgetDialogTextBlock->SetText(FText::FromString(DialogItem->TextLine));
	}
}

void ADinoJAMGameModeBase::OnDialogSoundFinish()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

	if(CurrentDialogItem->AutomaticPlayNextDialog)
	{
		if(Dialogs.Num() > 0)
		{
			if(DelayToNextDialogTimerHandle.IsValid())
				GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);

			GetWorld()->GetTimerManager().SetTimer(DelayToNextDialogTimerHandle, this, &ADinoJAMGameModeBase::PlayNextDialog, CurrentDialogItem->DelayToNextDialog);
		}
	}
}

void ADinoJAMGameModeBase::PlayNextDialog()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
	if(Dialogs.Num() > 0)
	{
		UDialogItem* DialogItem = Dialogs[0].GetDefaultObject();
		Dialogs.RemoveAt(0);

		PlayDialog(DialogItem);
	}
	else
	{
		if(WidgetDialogText)
		{
			WidgetDialogTextBlock->SetText(FText::FromString(""));

			if(WidgetDialogText->IsInViewport())
				WidgetDialogText->RemoveFromViewport();
		}

		if(DialogAudioComponent != nullptr)
			DialogAudioComponent->Stop();

		OnDialogSystemFinish(CurrentDialogItem);
	}
}

void ADinoJAMGameModeBase::OnDialogSystemFinish(UDialogItem* DialogItem)
{
	if(DialogItem->PlayerCharacter)
		DialogItem->PlayerCharacter->OnDialogFinish();
	
	if(OnDialogFinish.IsBound())
		OnDialogFinish.Execute(CurrentDialogItem);
}

void ADinoJAMGameModeBase::StartQuest(UQuest* Quest)
{
	if (qCurrentQuest)
		qCurrentQuest->OnQuestFinish(GetWorld());

	qCurrentQuest = Quest;

	qCurrentQuest->OnQuestStart(GetWorld());
}
