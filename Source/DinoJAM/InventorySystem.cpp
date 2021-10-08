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
			TArray<UItemSlot*, TFixedAllocator<SLOTS_SIZE>> Slots;
			
			for(int i = 0; i < SLOTS_SIZE; i++)
			{
				FString WidgetName = "I_Button_" + FString::FromInt(i);

				UItemSlot* ItemSlot = NewObject<UItemSlot>();

				ItemSlot->ButtonSlot = Cast<UItemButton>(InventoryWidget->GetWidgetFromName(FName(WidgetName)));
				ItemSlot->ButtonSlot->Index = i;
				ItemSlot->ButtonSlot->OnItemButtonClicked.BindUObject(this, &UInventorySystem::OnItemSelect);
				
				Slots.Add(ItemSlot);
			}

			ItemSlots = Slots;
		}
	}
}

void UInventorySystem::ShowInventory() const
{
	if(InventoryWidget)
	{
		if(!InventoryWidget->IsInViewport())
			InventoryWidget->AddToViewport(2);
	}
}

void UInventorySystem::HideInventory() const
{
	if(InventoryWidget)
	{
		if(InventoryWidget->IsInViewport())
			InventoryWidget->RemoveFromViewport();
	}
}

void UInventorySystem::OnItemSelect(int Index) const
{
	if(ItemSlots[Index]->Item)
	{
		if(ItemSlots[Index]->Item->bCanUse)
		{
			ItemSlots[Index]->Item->UseItem();

			ItemSlots[Index]->Item = nullptr;
			ItemSlots[Index]->ButtonSlot->WidgetStyle.Normal.SetResourceObject(DefaultItemSlotThumbNail);
			ItemSlots[Index]->ButtonSlot->WidgetStyle.Hovered.SetResourceObject(DefaultItemSlotThumbNail);
			ItemSlots[Index]->ButtonSlot->WidgetStyle.Pressed.SetResourceObject(DefaultItemSlotThumbNail);
		}
	}
}

void UInventorySystem::AddItem(AItem* NewItem)
{
	for(UItemSlot* Slot : ItemSlots)
	{
		if(!Slot->Item)
		{
			Slot->Item = NewItem;
			Slot->ButtonSlot->WidgetStyle.Normal.SetResourceObject(NewItem->ItemThumbnail);
			Slot->ButtonSlot->WidgetStyle.Hovered.SetResourceObject(NewItem->ItemThumbnail);
			Slot->ButtonSlot->WidgetStyle.Pressed.SetResourceObject(NewItem->ItemThumbnail);

			break;
		}
	}
}

AItem* UInventorySystem::GetItem(int Index)
{
	return ItemSlots[Index]->Item;
}