// Fill out your copyright notice in the Description page of Project Settings.


#include "MrAussichtPack.h"

#include "InventorySystem.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMrAussichtPack::AMrAussichtPack()
{
	bCanUse = false;
}


void AMrAussichtPack::BeginPlay()
{
	Super::BeginPlay();

	if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGameInstance->InventorySystem->AddItem(this);
	}
}

void AMrAussichtPack::UseItem()
{
	
}
