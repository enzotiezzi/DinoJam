// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreen.h"

#include "DinoJAMGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATitleScreen::ATitleScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(MyGameMode)
	{
		MyGameMode->StartTitleScreen();
	}
}

// Called every frame
void ATitleScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

