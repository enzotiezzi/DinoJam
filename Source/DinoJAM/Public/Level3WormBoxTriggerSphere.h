// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WormBook.h"
#include "DinoJAM/Dialog.h"
#include "DinoJAM/Interactable.h"
#include "Engine/TriggerSphere.h"
#include "Level3WormBoxTriggerSphere.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ALevel3WormBoxTriggerSphere : public ATriggerSphere, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(APS1Character* Interactor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSubclassOf<AWormBook> WormBookRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	TSubclassOf<UDialog> DialogRef;
};
