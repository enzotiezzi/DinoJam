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
		CurrentInteractor->StartDialog();

		UpdateDialogAnimationOwner(MyGameMode->qCurrentQuest->Dialog, CurrentInteractor);
		MyGameMode->StartDialogSystem(MyGameMode->qCurrentQuest->Dialog, MyGameMode->qCurrentQuest->OnDialogFinish);
	}
}

void AKaren::UpdateDialogAnimationOwner(TArray<TSubclassOf<UDialogItem>> Dialog, APlayerCharacter* Interactor)
{
	for (TSubclassOf<UDialogItem> DialogItem : Dialog)
	{
		if(DialogItem)
		{
			UDialogItem* Item = Cast<UDialogItem>(DialogItem->GetDefaultObject());
			
			Item->OwnerCharacter = this;
			Item->PlayerCharacter = Interactor;
		}
	}
}