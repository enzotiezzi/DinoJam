// Fill out your copyright notice in the Description page of Project Settings.


#include "Level2InitialQuestTrigger.h"

#include "DialogSystem.h"
#include "Level2InitialQuest.h"
#include "LevelSequenceActor.h"
#include "MyGameInstance.h"
#include "Niece.h"
#include "PlayerCharacter.h"
#include "QuestSystem.h"
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
			ULevel2InitialQuest* Quest = Cast<ULevel2InitialQuest>(MyGameInstance->QuestSystem->GetCurrentQuest());

			if(Quest)
			{
				ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

				if(MyGameMode)
				{
					FRotator AmountOfRotationToNiece = UKismetMathLibrary::FindLookAtRotation(OtherActor->GetActorLocation(), Niece->GetActorLocation());
					AmountOfRotationToNiece.Pitch = 0;
					AmountOfRotationToNiece.Roll = 0;

					FRotator AmountOfRotationToPlayer = UKismetMathLibrary::FindLookAtRotation(Niece->GetActorLocation(), OtherActor->GetActorLocation());
					AmountOfRotationToPlayer.Pitch = 0;
					AmountOfRotationToPlayer.Roll = 0;

					OtherActor->SetActorRelativeRotation(FQuat(AmountOfRotationToNiece));
					Niece->SetActorRelativeRotation(FQuat(AmountOfRotationToPlayer));
					
					MyGameMode->DialogSystem->StartDialogSystem(Quest->StartingDialog.GetDefaultObject(), Cast<APlayerCharacter>(OtherActor), Niece);

					BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				}
			}
		}
	}
}
