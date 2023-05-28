// Fill out your copyright notice in the Description page of Project Settings.


#include "WormPack.h"

#include "DinoJAM/InventorySystem.h"
#include "DinoJAM/MyGameInstance.h"
#include "DinoJAM/PianoBox.h"
#include "DinoJAM/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void AWormPack::BeginPlay()
{
	Super::BeginPlay();
	
	if(const UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		MyGameInstance->InventorySystem->AddItem(this);
	}
}

void AWormPack::UseItem()
{
	if (bCanUse)
	{
		if (BoxReference)
		{
			const UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (MyGameInstance)
			{
				APianoBox* Box = GetWorld()->SpawnActor<APianoBox>(BoxReference, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());

				MyGameInstance->CurrentPlayerCharacter->CarryPackage(Box);

				const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;

				Box->PianoBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Box->PianoBoxComponent->AttachToComponent(MyGameInstance->CurrentPlayerCharacter->GetMesh(), AttachmentTransformRules, FName("PianoBoxSocket"));

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
			}
		}
	}
}
