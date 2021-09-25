// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleWall.h"

#include "Components/BoxComponent.h"

// Sets default values
AInvisibleWall::AInvisibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void AInvisibleWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvisibleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

