// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level2SetupGlassesQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel2SetupGlassesQuest : public UQuest
{
	GENERATED_BODY()

public:
	virtual void OnQuestStart(UWorld* World) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Starting Dialog")
	TSubclassOf<UDialog> StartingDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Starting Dialog")
	TSubclassOf<UDialog> FinishDialog;

protected:
	void OnMainDialogFinish(UDialogItem* DialogItem);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> WidgetSignatureReference;

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* WidgetSignature;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	float RemoveSignatureWidgetInSeconds = 2.5;
};
