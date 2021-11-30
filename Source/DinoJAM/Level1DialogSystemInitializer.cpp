// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1DialogSystemInitializer.h"

#include "DinoJAMGameModeBase.h"
#include "Karen.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevel1DialogSystemInitializer::ALevel1DialogSystemInitializer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevel1DialogSystemInitializer::BeginPlay()
{
	Super::BeginPlay();

	if(Karen)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			MyGameInstance->CurrentNPC = Karen;
		}
	}
}

// Called every frame
void ALevel1DialogSystemInitializer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

