// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

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

	FOnDialogFinish OnDialogFinishTest;
	OnDialogFinishTest.BindUObject(this, &ADinoJAMGameModeBase::TestDialogFinish);

	StartDialogSystem(TArray<struct FDialogItem>(), OnDialogFinishTest);
}

void ADinoJAMGameModeBase::StartDialogSystem(TArray<struct FDialogItem> NewDialogs, FOnDialogFinish OnNewDialogFinish)
{
	//Dialogs = NewDialogs;
	this->OnDialogFinish = OnNewDialogFinish;

	if(Dialogs.Num() > 0)
	{
		const FDialogItem DialogItem = Dialogs[0];
		Dialogs.RemoveAt(0);

		PlayDialog(DialogItem);
	}
}

void ADinoJAMGameModeBase::PlayDialog(FDialogItem DialogItem)
{
	if(DialogAudioComponent != nullptr)
		DialogAudioComponent->Stop();
	
	CurrentDialogItem = DialogItem;
	
	DialogAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), DialogItem.Sound);

	if(CurrentDialogSoundTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

	if(DelayToNextDialogTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);

	if(DialogItem.Sound)
		GetWorld()->GetTimerManager().SetTimer(CurrentDialogSoundTimerHandle, this, &ADinoJAMGameModeBase::OnDialogSoundFinish, DialogItem.Sound->Duration);

	if(!WidgetDialogText->IsInViewport())
		WidgetDialogText->AddToViewport();

	WidgetDialogTextBlock->SetText(FText::FromString(DialogItem.TextLine));
}

void ADinoJAMGameModeBase::OnDialogSoundFinish()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

	if(CurrentDialogItem.AutomaticPlayNextDialog)
	{
		if(Dialogs.Num() > 0)
		{
			if(DelayToNextDialogTimerHandle.IsValid())
				GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);

			GetWorld()->GetTimerManager().SetTimer(DelayToNextDialogTimerHandle, this, &ADinoJAMGameModeBase::PlayNextDialog, CurrentDialogItem.DelayToNextDialog);
		}
	}
}

void ADinoJAMGameModeBase::PlayNextDialog()
{
	GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
	if(Dialogs.Num() > 0)
	{
		const FDialogItem DialogItem = Dialogs[0];
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

		if(OnDialogFinish.IsBound())
			OnDialogFinish.Execute(CurrentDialogItem);
	}
}

void ADinoJAMGameModeBase::TestDialogFinish(FDialogItem DialogItem)
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Red, DialogItem.TextLine);
}
