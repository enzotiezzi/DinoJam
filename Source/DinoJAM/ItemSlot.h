// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API UItemSlot : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	class UItemButton* ButtonSlot;

	UPROPERTY(BlueprintReadWrite)
	class AItem* Item;
};