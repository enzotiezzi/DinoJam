// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include <DinoJAM/DinoJAMGameModeBase.h>

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MyGameMode->AudioManager = this;

	if (!EnvironmentAudioComponent)
	{
		EnvironmentAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), EnvironmentSound);

		EnvironmentAudioComponent->Play();

		GEngine->AddOnScreenDebugMessage(rand(), 1, FColor::Red, "Playing Environment Music");
	}

	for (USoundBase* sound : Sounds)
	{
		UAudioComponent* SoundComponent = UGameplayStatics::CreateSound2D(GetWorld(), sound);
		SoundComponent->Play();

		SoundsAudioComponent.Add(SoundComponent);
	}
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}