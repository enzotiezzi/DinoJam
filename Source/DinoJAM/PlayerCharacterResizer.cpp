// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterResizer.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacterResizer::APlayerCharacterResizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacterResizer::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if(Character)
	{
		Character->SetActorRelativeScale3D(NewScale);
		Character->GetCharacterMovement()->MaxWalkSpeed = 50.0;
	}
}

// Called every frame
void APlayerCharacterResizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

