// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "MrAussichtPack.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API AMrAussichtPack : public AItem
{
	GENERATED_BODY()

public:
	AMrAussichtPack();
	
	virtual void BeginPlay() override;

	virtual void UseItem() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Box")
	class TSubclassOf<class APianoBox> BoxReference;
};
