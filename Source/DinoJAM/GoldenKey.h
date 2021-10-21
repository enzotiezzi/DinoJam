// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GoldenKey.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API AGoldenKey : public AItem
{
	GENERATED_BODY()

public:
	AGoldenKey();

	virtual void UseItem() override;
};
