// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2InitialQuestTrigger.h"

#include "Level2InitialQuest.h"
#include "MyGameInstance.h"
#include "Niece.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALevel2InitialQuestTrigger::ALevel2InitialQuestTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void ALevel2InitialQuestTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevel2InitialQuestTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevel2InitialQuestTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(Cast<APlayerCharacter>(OtherActor))
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if(MyGameInstance)
		{
			ULevel2InitialQuest* Quest = Cast<ULevel2InitialQuest>(MyGameInstance->qCurrentQuest);

			if(Quest)
			{
				ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

				if(MyGameMode)
				{
					FRotator AmountOfRotationToNiece = UKismetMathLibrary::FindLookAtRotation(OtherActor->GetActorLocation(), Niece->GetActorLocation());
					AmountOfRotationToNiece.Pitch = 0;
					AmountOfRotationToNiece.Roll = 0;

					OtherActor->SetActorRelativeRotation(FQuat(AmountOfRotationToNiece));
					
					MyGameMode->StartDialogSystem(Quest->StartingDialog, Quest->OnStartingDialogFinish, Cast<APlayerCharacter>(OtherActor), Niece);

					BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				}
			}
		}
	}
}
