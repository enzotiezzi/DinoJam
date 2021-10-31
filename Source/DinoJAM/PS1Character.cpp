// Fill out your copyright notice in the Description page of Project Settings.


#include "PS1Character.h"

#include "Components/SphereComponent.h"

// Sets default values
APS1Character::APS1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SphereComponent->SetupAttachment(GetRootComponent());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FQuat(FRotator(0.0, -90.0, 0.0)));
}

// Called when the game starts or when spawned
void APS1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APS1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APS1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

