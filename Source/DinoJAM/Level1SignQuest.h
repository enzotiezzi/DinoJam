// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1SignQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1SignQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;

protected:
	void OnDialogFinish(UDialogItem* DialogItem);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> WidgetSignatureReference;

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* WidgetSignature;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	float RemoveSignatureWidgetInSeconds = 2.5;
};
