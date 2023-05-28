// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAM/Item.h"
#include "WormPack.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API AWormPack : public AItem
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void UseItem() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Box")
	TSubclassOf<class APianoBox> BoxReference;
};
