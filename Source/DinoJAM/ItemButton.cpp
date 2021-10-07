// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemButton.h"

UItemButton::UItemButton()
{
	this->OnClicked.AddDynamic(this, &UItemButton::OnClick);
}

void UItemButton::OnClick()
{
	OnItemButtonClicked.ExecuteIfBound(Index);
}
