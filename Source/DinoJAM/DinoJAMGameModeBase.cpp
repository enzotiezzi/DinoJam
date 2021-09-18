// Copyright Epic Games, Inc. All Rights Reserved.


#include "DinoJAMGameModeBase.h"

#include "Blueprint/UserWidget.h"
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

	PlayDialog(Dialogs[0]);
}

void ADinoJAMGameModeBase::PlayDialog(FDialogItem DialogItem)
{
	UGameplayStatics::PlaySound2D(GetWorld(), DialogItem.Sound);

	if(CurrentDialogSoundTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);
	
	GetWorld()->GetTimerManager().SetTimer(CurrentDialogSoundTimerHandle, this, &ADinoJAMGameModeBase::OnDialogSoundFinish, DialogItem.Sound->Duration);

	WidgetDialogText->AddToViewport();

	WidgetDialogTextBlock->SetText(FText::FromString(DialogItem.TextLine));
}

void ADinoJAMGameModeBase::OnDialogSoundFinish()
{
	if(WidgetDialogText)
	{
		WidgetDialogTextBlock->SetText(FText::FromString(""));

		WidgetDialogText->RemoveFromViewport();
	}
}