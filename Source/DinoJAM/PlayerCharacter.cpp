// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DinoJAMGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Interact()
{
	if(bIsOnDialog)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

		if (MyGameMode)
		{
			MyGameMode->PlayNextDialog();
		}
	}
}

void APlayerCharacter::OnDialogFinish()
{
	bIsOnDialog = false;
}
