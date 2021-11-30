// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

// Sets default values
AObjective::AObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Game/itens/Quest_Arrow/Quest_Arrow"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationFinder(TEXT("/Game/itens/Quest_Arrow/BPA_Quest_Arrow"));
	
	SetRootComponent(SkeletalMeshComponent);
	
	if(SkeletalMeshFinder.Object)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshFinder.Object);

		if(AnimationFinder.Object)
		{
			SkeletalMeshComponent->SetAnimInstanceClass(AnimationFinder.Object->GeneratedClass);
		}
	}

	SkeletalMeshComponent->SetRelativeScale3D(FVector(.3, .3, .3));

	SkeletalMeshComponent->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjective::ShowIndicator() const
{
	SkeletalMeshComponent->SetHiddenInGame(false);
}

void AObjective::HideIndicator() const
{
	SkeletalMeshComponent->SetHiddenInGame(true);
}
