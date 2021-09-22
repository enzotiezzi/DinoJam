// Fill out your copyright notice in the Description page of Project Settings.


#include "Karen.h"

#include "Level1InitialQuest.h"
#include "PlayerCharacter.h"
#include "UQuest.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKaren::AKaren()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FQuat(FRotator(0.0, -90.0, 0.0)));

	SphereComponent->SetupAttachment(GetRootComponent());
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

void AKaren::Interact(ACharacter* Interactor)
{
	this->CurrentInteractor = Cast<APlayerCharacter>(Interactor);
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

	if(MyGameMode)
	{
		TArray<TSubclassOf<class UDialogItem>> DialogToBeUsed;
		FOnDialogFinish OnDialogFinishToBeUsed;
		
		if(MyGameMode->qCurrentQuest->bComplexCondition)
		{
			DialogToBeUsed = MyGameMode->qCurrentQuest->GetDialogBasedOnComplexCondition();
			OnDialogFinishToBeUsed = MyGameMode->qCurrentQuest->GetOnDialogFinishBasedOnComplexCondition();
		}
		else
		{
			DialogToBeUsed = MyGameMode->qCurrentQuest->Dialog;
			OnDialogFinishToBeUsed = MyGameMode->qCurrentQuest->OnDialogFinish;
		}

		MyGameMode->StartDialogSystem(DialogToBeUsed, OnDialogFinishToBeUsed, CurrentInteractor, this);
	}
}
