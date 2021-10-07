// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

#include "ItemButton.h"
#include "ItemSlot.h"
#include "Blueprint/UserWidget.h"

UInventorySystem::UInventorySystem()
{
}

void UInventorySystem::SetupInventoryWidget(UWorld* World)
{
	if(InventoryWidgetReference)
	{
		InventoryWidget = CreateWidget<UUserWidget>(World, InventoryWidgetReference);

		if(InventoryWidget)
		{
			for(int i = 0; i < SLOTS_SIZE; i++)
			{
				FString WidgetName = "Inventory_Button_" + FString::FromInt(i);

				UItemSlot* ItemSlot = NewObject<UItemSlot>();

				ItemSlots[i] = ItemSlot;
				ItemSlots[i]->ButtonSlot = Cast<UItemButton>(InventoryWidget->GetWidgetFromName(FName(WidgetName)));
				ItemSlots[i]->ButtonSlot->Index = i;
				ItemSlots[i]->ButtonSlot->OnItemButtonClicked.BindUObject(this, &UInventorySystem::OnItemSelect);
			}
		}
	}
}

void UInventorySystem::ShowInventory() const
{
	if(InventoryWidget)
		InventoryWidget->AddToViewport();
}

void UInventorySystem::HideInventory() const
{
	if(InventoryWidget)
		InventoryWidget->RemoveFromViewport();
}

void UInventorySystem::OnItemSelect(int Index) const
{
	if(ItemSlots[Index]->Item)
		ItemSlots[Index]->Item->UseItem();
}

void UInventorySystem::AddItem(AItem* NewItem)
{
	for(UItemSlot* Slot : ItemSlots)
	{
		if(!Slot->Item)
		{
			Slot->Item = NewItem;
			Slot->ButtonSlot->WidgetStyle.Normal.SetResourceObject(NewItem->ItemThumbnail);
		}
	}
}
