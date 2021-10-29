// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerableDialog.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerableDialog::ATriggerableDialog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void ATriggerableDialog::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerableDialog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerableDialog::Interact(APS1Character* Interactor)
{
	if(Cast<APlayerCharacter>(Interactor))
	{
		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if(MyGameMode)
		{
			MyGameMode->StartDialogSystem(InteractableDialog, OnInteractableDialogFinish, Cast<APlayerCharacter>(Interactor), nullptr);
		}
	}
}
