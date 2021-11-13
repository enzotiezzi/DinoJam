// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <any>

#include "Item.h"
#include "ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
	
	UPROPERTY(BlueprintReadWrite)
	class UWorld* CurrentWorld;
	
	void AddItem(AItem* NewItem);

	template <typename T>
	AItem* GetItem()
	{
		for (UItemSlot* Slot : ItemSlots)
		{
			if(Slot->Item)
			{
				if(Slot->Item->IsA<T>())
					return Slot->Item;
			}
		}
	
		return nullptr;
	}
	
	///////////////////////////////////////////
	///
	/// UI
	///
	///////////////////////////////////////////
	void SetupInventoryWidget(UWorld* World);

	void SetupItemPopUpWidget(UWorld* World);
	
	void ShowInventory() const;

	void HideInventory() const;

	void ShowItemPopUp(UTexture2D* ItemImage, FString ItemDescription) const;

	bool IsOpened() const
	{
		return InventoryWidget->IsInViewport();
	}

protected:
	/////////////////////////////////////////////
	///
	/// UI
	///
	/////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> InventoryWidgetReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> ItemPopUpWidgetReference;

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* InventoryWidget;

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* ItemPopUpWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Thumbnail")
	class UTexture2D* DefaultItemSlotThumbNail;
	
	//////////////////////////////////////////////
	///
	/// ITEM
	///
	//////////////////////////////////////////////
	static const int SLOTS_SIZE = 6;

	UPROPERTY()
	TArray<class UItemSlot*> ItemSlots;
	
	void OnItemSelect(int Index) const;

	UPROPERTY(BlueprintReadWrite)
	UImage* ItemPopUpImage;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* ItemPopUpText;
};