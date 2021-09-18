// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DinoJAMGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FDialogItem
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundBase* Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TextLine")
	FString TextLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character")
	class ACharacter* OwnerCharacter;
};

/**
 * 
 */
UCLASS()
class DINOJAM_API ADinoJAMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void PlayDialog(FDialogItem DialogItem);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> WidgetDialogTextReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<struct FDialogItem> Dialogs;

protected:
	UPROPERTY()
	class UUserWidget* WidgetDialogText;

	UPROPERTY()
	class UTextBlock* WidgetDialogTextBlock;

	UPROPERTY()
	struct FTimerHandle CurrentDialogSoundTimerHandle;
	void OnDialogSoundFinish();
};

