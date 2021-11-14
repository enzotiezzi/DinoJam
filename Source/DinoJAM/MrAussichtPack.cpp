// Fill out your copyright notice in the Description page of Project Settings.


#include "MrAussichtPack.h"

#include "InventorySystem.h"
#include "MyGameInstance.h"
#include "PianoBox.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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
	if(BoxReference)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			APianoBox* Box = GetWorld()->SpawnActor<APianoBox>(BoxReference, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());

			MyGameInstance->CurrentPlayerCharacter->CarryPianoBox();
			
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

			Box->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Box->PianoBoxComponent->AttachToComponent(MyGameInstance->CurrentPlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
		}
	}
}
