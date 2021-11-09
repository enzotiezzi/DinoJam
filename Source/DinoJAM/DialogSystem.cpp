// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogSystem.h"

#include "Dialog.h"
#include "LevelSequenceActor.h"
#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UDialogSystem::SetupDialogSystemWidget()
{
	if(WidgetDialogTextReference)
	{
		WidgetDialogText = CreateWidget<UUserWidget>(CurrentWorld, WidgetDialogTextReference);

		if(WidgetDialogText)
		{
			WidgetDialogTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_Dialog"));
			WidgetCharacterNameTextBlock = Cast<UTextBlock>(WidgetDialogText->GetWidgetFromName("TextBlock_CharacterName"));
		}
	}
}

void UDialogSystem::StartDialogSystem(class UDialog* Dialog)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));

	if(MyGameInstance)
	{
		StartDialogSystem(Dialog, MyGameInstance->CurrentPlayerCharacter, MyGameInstance->CurrentNPC);
	}
}

void UDialogSystem::StartDialogSystem(class UDialog* Dialog, APlayerCharacter* PlayerCharacter, APS1Character* NPC)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));

	if(MyGameInstance)
	{
		CurrentDialog = Dialog;
		Dialogs = Dialog->Dialogs;
		OnDialogFinish = Dialog->OnDialogFinish;
		MyGameInstance->CurrentPlayerCharacter = PlayerCharacter;
		MyGameInstance->CurrentNPC = NPC;

		MyGameInstance->CurrentPlayerCharacter->StartDialog();

		if(Dialogs.Num() > 0)
		{
			UDialogItem* DialogItem = Dialogs[0].GetDefaultObject();
			Dialogs.RemoveAt(0);

			PlayDialog(DialogItem);
		}
	}
}

void UDialogSystem::PlayDialog(UDialogItem* DialogItem)
{
	if(DialogItem)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));

		if(MyGameInstance)
		{
			if(MyGameInstance->CurrentPlayerCharacter)
			{
				if(DialogItem->PlayerAnimation)
					MyGameInstance->CurrentPlayerCharacter->PlayAnimMontage(DialogItem->PlayerAnimation);
				else
					MyGameInstance->CurrentPlayerCharacter->StopAnimMontage();

				if(DialogItem->PlayerFaceExpressionMaterial)
					MyGameInstance->CurrentPlayerCharacter->GetMesh()->SetMaterial(MyGameInstance->CurrentPlayerCharacter->FaceMaterialIndex, DialogItem->PlayerFaceExpressionMaterial);
			}

			if(MyGameInstance->CurrentNPC)
			{
				if(DialogItem->NPCAnimation)
					MyGameInstance->CurrentNPC->PlayAnimMontage(DialogItem->NPCAnimation);
				else
					MyGameInstance->CurrentNPC->StopAnimMontage();
				
				if(DialogItem->NPCFaceExpressionMaterial)
					MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, DialogItem->NPCFaceExpressionMaterial);
				else
					MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(MyGameInstance->CurrentNPC->FaceMaterialIndex, MyGameInstance->CurrentNPC->DefaultFaceExpression);

				for(FFaceExpression FaceExpression : DialogItem->ExtraFaceExpressions)
				{
					MyGameInstance->CurrentNPC->GetMesh()->SetMaterial(FaceExpression.Index, FaceExpression.FaceExpressionMaterial);
				}
			}

			if(DialogItem->Sequence)
			{
				if(CurrentSequencePlayer)
				{
					CurrentSequencePlayer->Stop();
				}
				
				ALevelSequenceActor* LevelSequenceActor;
				
				FMovieSceneSequencePlaybackSettings MovieSceneSequencePlaybackSettings;
				MovieSceneSequencePlaybackSettings.bPauseAtEnd = true;

				CurrentSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(CurrentWorld, DialogItem->Sequence, MovieSceneSequencePlaybackSettings,LevelSequenceActor);

				if(CurrentSequencePlayer)
				{
					CurrentSequencePlayer->Play();
				}
			}
			else
			{
				if(CurrentSequencePlayer)
				{
					CurrentSequencePlayer->Stop();
				}
			}

			if(DialogAudioComponent != nullptr)
				DialogAudioComponent->Stop();
	
			CurrentDialogItem = DialogItem;
			CurrentDialogItem->World = CurrentWorld;

			if(CurrentDialogSoundTimerHandle.IsValid())
				CurrentWorld->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

			if(DelayToNextDialogTimerHandle.IsValid())
				CurrentWorld->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
			if(DialogItem->Sound)
			{
				CurrentWorld->GetTimerManager().SetTimer(CurrentDialogSoundTimerHandle, this, &UDialogSystem::OnDialogSoundFinish, DialogItem->Sound->Duration);

				DialogAudioComponent = UGameplayStatics::SpawnSound2D(CurrentWorld, DialogItem->Sound);
			}

			if(!WidgetDialogText->IsInViewport())
				WidgetDialogText->AddToViewport();

			FText DialogOwnerText;

			if(DialogItem->DialogOwner == EDialogOwner::PLAYER)
				DialogOwnerText = FText::FromString(MyGameInstance->CurrentPlayerCharacter->CharacterName);
			else
			{
				if(MyGameInstance->CurrentNPC)
					DialogOwnerText = FText::FromString(MyGameInstance->CurrentNPC->CharacterName);
			}

			WidgetCharacterNameTextBlock->SetText(DialogOwnerText);
			WidgetDialogTextBlock->SetText(FText::FromString(DialogItem->TextLine));
		}
	}
}

void UDialogSystem::OnDialogSoundFinish()
{
	CurrentWorld->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);

	if(CurrentDialogItem->AutomaticPlayNextDialog)
	{
		if(Dialogs.Num() > 0)
		{
			if(DelayToNextDialogTimerHandle.IsValid())
				CurrentWorld->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);

			CurrentWorld->GetTimerManager().SetTimer(DelayToNextDialogTimerHandle, this, &UDialogSystem::PlayNextDialog, CurrentDialogItem->DelayToNextDialog);
		}
	}
}

void UDialogSystem::PlayNextDialog()
{
	CurrentWorld->GetTimerManager().ClearTimer(CurrentDialogSoundTimerHandle);
	CurrentWorld->GetTimerManager().ClearTimer(DelayToNextDialogTimerHandle);
	
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

void UDialogSystem::OnDialogSystemFinish(UDialogItem* DialogItem)
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentPlayerCharacter)
			MyGameInstance->CurrentPlayerCharacter->OnDialogFinish();
	
		if(OnDialogFinish.IsBound())
			OnDialogFinish.Execute(CurrentDialogItem);

		CurrentDialog->OnDialogFinished(CurrentDialogItem);
	}
}