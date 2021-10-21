// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Gear.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API AGear : public AItem
{
	GENERATED_BODY()

public:
	AGear();

	virtual void UseItem() override;
};
