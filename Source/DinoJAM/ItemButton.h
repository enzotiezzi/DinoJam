// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ItemButton.generated.h"

DECLARE_DELEGATE_OneParam(FOnItemButtonClicked, int);

/**
 * 
 */
UCLASS()
class DINOJAM_API UItemButton : public UButton
{
	GENERATED_BODY()

public:
	UItemButton();

	int Index = -1;
	
	FOnItemButtonClicked OnItemButtonClicked;

protected:
	UFUNCTION()
	void OnClick();
};
