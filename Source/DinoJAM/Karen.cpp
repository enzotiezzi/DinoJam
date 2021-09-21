// Fill out your copyright notice in the Description page of Project Settings.


#include "Karen.h"

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

	OnDialogBeforeLevelFinish.BindUObject(this, &AKaren::OnDialogBeforeLevelFinished);
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

void AKaren::Interact(APlayerCharacter* Interactor)
{
	this->CurrentInteractor = Interactor;
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

	ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

	if(MyGameMode)
	{
		Interactor->StartDialog();
		
		MyGameMode->StartDialogSystem(DialogBeforeLevel, OnDialogBeforeLevelFinish);
	}
}

void AKaren::UpdateDialogAnimationOwner(TArray<FDialogItem> Dialog, ACharacter* Interactor)
{
	for (FDialogItem DialogItem : Dialog)
	{
		DialogItem.OwnerCharacter = this;
		DialogItem.PlayerCharacter = Interactor;
	}
}

void AKaren::OnDialogBeforeLevelFinished(FDialogItem DialogItem)
{
	if(CurrentInteractor)
		CurrentInteractor->OnDialogFinish();
}
