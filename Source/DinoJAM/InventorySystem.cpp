// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

#include "DinoJAMGameModeBase.h"
#include "ItemButton.h"
#include "ItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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

void UInventorySystem::SetupItemPopUpWidget(UWorld* World)
{
	if(ItemPopUpWidgetReference)
	{
		ItemPopUpWidget = CreateWidget<UUserWidget>(World, ItemPopUpWidgetReference);

		if(ItemPopUpWidget)
		{
			ItemPopUpImage = Cast<UImage>(ItemPopUpWidget->GetWidgetFromName("Image_Item_Thumbnail"));
			ItemPopUpText = Cast<UTextBlock>(ItemPopUpWidget->GetWidgetFromName("TextBlock_Item_Description"));
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

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	
	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentPlayerCharacter)
		{
			APlayerController* PlayerController = Cast<APlayerController>(MyGameInstance->CurrentPlayerCharacter->GetController());

			if(PlayerController)
			{
				FInputModeGameAndUI InputMode;
				InputMode.SetWidgetToFocus(ItemSlots[0]->ButtonSlot->TakeWidget());
				
				MyGameInstance->CurrentPlayerCharacter->StopMoving();
				
				PlayerController->SetInputMode(InputMode);
				PlayerController->SetShowMouseCursor(true);
			}
		}
	}
}

void UInventorySystem::HideInventory() const
{
	if(InventoryWidget)
	{
		if(InventoryWidget->IsInViewport())
			InventoryWidget->RemoveFromViewport();
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));

	if(MyGameInstance)
	{
		if(MyGameInstance->CurrentPlayerCharacter)
		{
			APlayerController* PlayerController = Cast<APlayerController>(MyGameInstance->CurrentPlayerCharacter->GetController());

			if(PlayerController)
			{
				MyGameInstance->CurrentPlayerCharacter->ContinueMoving();
				
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->SetShowMouseCursor(false);
			}
		}
	}
}

void UInventorySystem::OnItemSelect(int Index) const
{
	if(ItemSlots[Index]->Item)
	{
		if(ItemSlots[Index]->Item->bCanUse)
		{
			if(ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(ItemSlots[Index]->Item->GetWorld())))
			{
				MyGameMode->ResumeGame();
			}
			
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

AItem* UInventorySystem::GetItem(UClass* ClassType)
{
	for (UItemSlot* Slot : ItemSlots)
	{
		if(Slot->Item)
		{
			if(Slot->Item->GetClass()->GetSuperClass() == ClassType)
				return Slot->Item;
		}
	}
	
	return nullptr;
}

void UInventorySystem::ShowItemPopUp(UTexture2D* ItemImage, FString ItemDescription) const
{
	if(ItemPopUpWidget)
	{
		ItemPopUpImage->Brush.SetResourceObject(ItemImage);
		ItemPopUpText->SetText(FText::FromString(ItemDescription));

		if(!ItemPopUpWidget->IsInViewport())
		{
			ItemPopUpWidget->AddToViewport();
		}
	}
}
