//Copyright 1998-2021 Epic Games, Inc. All Rights Reserved.

#include "BlendTriggerVolume.h"

#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABlendTriggerVolume::ABlendTriggerVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraProximityVolume"));
	OverlapVolume->SetupAttachment(RootComponent);

	CameraToFind = CreateDefaultSubobject<ACameraActor>(TEXT("CameraToFind"));
}

// Called when the game starts or when spawned
void ABlendTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ABlendTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* PlayerCharacterCheck = Cast<APlayerCharacter>(OtherActor))
	{
		if (APlayerController* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			PlayerCharacterController->SetViewTargetWithBlend(CameraToFind, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

void ABlendTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (APlayerCharacter* PlayerCharacterCheck = Cast<APlayerCharacter>(OtherActor))
	{
		if (APlayerController* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			PlayerCharacterController->SetViewTargetWithBlend(PlayerCharacterController->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

// Called every frame
void ABlendTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}