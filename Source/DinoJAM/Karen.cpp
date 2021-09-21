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

		TArray<TSubclassOf<UDialogItem>> DialogToBeUsed;
		FOnDialogFinish OnDialogFinishToBeUsed;

		switch (MyGameMode->CurrentLevel1Quest)
		{
			case ELEVEL1_QUESTS::BEFORE_LEVEL:
				DialogToBeUsed = MyGameMode->DialogBeforeLevel;
			    OnDialogFinishToBeUsed = MyGameMode->OnDialogBeforeLevelFinish;
			break;
				
			case ELEVEL1_QUESTS::SETUP_PIANO:
				if(MyGameMode->bIsPianoSetup)
				{
					DialogToBeUsed = MyGameMode->DialogDuringSetupPiano;
					OnDialogFinishToBeUsed = MyGameMode->OnDialogDuringSetupPianoFinish;
				}
				else
				{
					DialogToBeUsed = MyGameMode->DialogBeforeSetupPiano;
					OnDialogFinishToBeUsed = MyGameMode->OnDialogBeforeSetupPianoFinish;
				}
				break;

			case ELEVEL1_QUESTS::BEFORE_FIND_HAMMER:
				DialogToBeUsed = MyGameMode->DialogBeforeFindHammer;
				OnDialogFinishToBeUsed = MyGameMode->OnDialogBeforeFindHammerFinish;
				break;

			case ELEVEL1_QUESTS::FIND_HAMMER:
				if(MyGameMode->bFoundHammer)
				{
					DialogToBeUsed = MyGameMode->DialogFoundHammer;
					OnDialogFinishToBeUsed = MyGameMode->OnDialogFoundHammerFinish;
				}
				else
				{
					DialogToBeUsed = MyGameMode->DialogNoHammer;
					OnDialogFinishToBeUsed = MyGameMode->OnDialogNoHammerFinish;
				}
				break;

			case ELEVEL1_QUESTS::BUILD_PIANO:
				DialogToBeUsed = MyGameMode->DialogBuildPiano;
				OnDialogFinishToBeUsed = MyGameMode->OnDialogBuildPianoFinish;
				break;

			case ELEVEL1_QUESTS::LEVEL_FINISH:
				DialogToBeUsed = MyGameMode->DialogBuildPiano;
				OnDialogFinishToBeUsed = MyGameMode->OnDialogBuildPianoFinish;
				break;

			case ELEVEL1_QUESTS::SIGN_PAPER:
				DialogToBeUsed = MyGameMode->DialogSignPaper;
				OnDialogFinishToBeUsed = MyGameMode->OnDialogSignPaperFinish;
				break;
			
			default:;
		}

		UpdateDialogAnimationOwner(DialogToBeUsed, Interactor);
		MyGameMode->StartDialogSystem(DialogToBeUsed, OnDialogFinishToBeUsed);
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