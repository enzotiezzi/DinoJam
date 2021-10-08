// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemSlot.h"
#include "UObject/NoExportTypes.h"
#include "InventorySystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DINOJAM_API UInventorySystem : public UObject
{
	GENERATED_BODY()

public:
	UInventorySystem();
	
	void AddItem(AItem* NewItem);
	
	///////////////////////////////////////////
	///
	/// UI
	///
	///////////////////////////////////////////
	void SetupInventoryWidget(UWorld* World);
	
	void ShowInventory() const;

	void HideInventory() const;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UWorld* CurrentWorld;

	/////////////////////////////////////////////
	///
	/// UI
	///
	/////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> InventoryWidgetReference;

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* InventoryWidget;
	//////////////////////////////////////////////
	///
	/// ITEM
	///
	//////////////////////////////////////////////
	static const int SLOTS_SIZE = 6;

	UPROPERTY()
	TArray<class UItemSlot*> ItemSlots;
	
	void OnItemSelect(int Index) const;
};