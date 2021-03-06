// Fill out your copyright notice in the Description page of Project Settings.


#include "Karen.h"

#include "DialogSystem.h"
#include "Level1InitialQuest.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
#include "UQuest.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKaren::AKaren()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FQuat(FRotator(0.0, -90.0, 0.0)));
}

// Called when the game starts or when spawned
void AKaren::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKaren::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKaren::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AKaren::Interact(APS1Character* Interactor)
{
	this->CurrentInteractor = Cast<APlayerCharacter>(Interactor);
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

	if(MyGameMode)
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			MyGameMode->DialogSystem->StartDialogSystem(MyGameInstance->QuestSystem->GetCurrentQuest()->GetDialog(GetClass()->GetSuperClass()).GetDefaultObject(), CurrentInteractor, this);
		}
	}
}
