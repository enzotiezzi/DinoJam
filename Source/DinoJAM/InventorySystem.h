// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemSlot.h"
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
	
	void AddItem(AItem* NewItem);

	AItem* GetItem(int Index);

	AItem* GetItem(UClass* ClassType);
	
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