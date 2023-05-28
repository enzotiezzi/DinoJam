// Fill out your copyright notice in the Description page of Project Settings.


#include "Level3Hallway1DialogInit.h"

#include "BookWorm.h"
#include "Level3WormBoxTriggerSphere.h"
#include "WormPack.h"
#include "DinoJAM/CutSceneManager.h"
#include "DinoJAM/DialogSystem.h"
#include "DinoJAM/InventorySystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevel3Hallway1DialogInit::ALevel3Hallway1DialogInit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevel3Hallway1DialogInit::BeginPlay()
{
	Super::BeginPlay();

	if (StarterDialog)
	{
		if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(
			UGameplayStatics::GetGameMode(GetWorld())))
		{
			FTimerHandle StartDialogTimerHandle;

			GetWorld()->GetTimerManager().SetTimer(StartDialogTimerHandle, [this, MyGameMode]()
			{
				UDialog* Dialog = StarterDialog.GetDefaultObject();
				Dialog->OnDialogFinish.BindUFunction(this, "OnStarterDialogFinish");

				MyGameMode->DialogSystem->StartDialogSystem(Dialog);
			}, .2, false);
		}
	}
}

// Called every frame
void ALevel3Hallway1DialogInit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevel3Hallway1DialogInit::OnStarterDialogFinish()
{
	if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (MyGameMode->CutsceneManager)
		{
			FOnMovieSceneSequencePlayerEvent Event;
			Event.AddDynamic(this, &ALevel3Hallway1DialogInit::OnSequenceFinish);

			MyGameMode->CutsceneManager->SetSequence(WormIntroSequence);
			MyGameMode->CutsceneManager->SetOnSceneFinished(Event);
			MyGameMode->CutsceneManager->PlayCurrentSequence();
		}
	}
}

void ALevel3Hallway1DialogInit::OnLastDialogFinish()
{
	if (Objective)
	{
		Objective->SetActorEnableCollision(true);
		Objective->ShowIndicator();
	}

	if (const UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		AItem* WormPack = MyGameInstance->InventorySystem->GetItem<AWormPack>();
		WormPack->bCanUse = true;
	}

	ABookWorm* BookWorm = Cast<ABookWorm>(UGameplayStatics::GetActorOfClass(GetWorld(), ABookWorm::StaticClass()));

	if (BookWorm)
	{
		BookWorm->bCanMove = true;
	}
}

void ALevel3Hallway1DialogInit::OnSequenceFinish()
{
	if (LastDialog)
	{
		if (const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(
			UGameplayStatics::GetGameMode(GetWorld())))
		{
			UDialog* Dialog = LastDialog.GetDefaultObject();
			Dialog->OnDialogFinish.BindUFunction(this, "OnLastDialogFinish");

			MyGameMode->DialogSystem->StartDialogSystem(Dialog);
			
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ALevel3WormBoxTriggerSphere* Trigger = Cast<ALevel3WormBoxTriggerSphere>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevel3WormBoxTriggerSphere::StaticClass())); 

			if(Trigger)
			{
				ABookWorm* BookWorm = GetWorld()->SpawnActor<ABookWorm>(BookWormRef, Trigger->GetActorLocation() + (Trigger->GetActorRightVector() * 80), FRotator(0, 90, 0), SpawnParameters);
				BookWorm->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
			}
		}
	}
}
