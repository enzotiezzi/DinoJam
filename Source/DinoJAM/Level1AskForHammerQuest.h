// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UQuest.h"
#include "Level1AskForHammerQuest.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1AskForHammerQuest : public UQuest
{
	GENERATED_BODY()
	
public:
	virtual void OnQuestStart(UWorld* World) override;

	virtual TSubclassOf<UDialog> GetDialog(UClass* Class) override;
	
	bool bHaveHammer = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> PreDialog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> DontHaveHammerDialog;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog System")
	TSubclassOf<class UDialog> HaveHammerDialog;

	void ExecuteOnDialogFinish(UDialogItem* DialogItem);
};