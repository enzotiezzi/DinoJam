// Fill out your copyright notice in the Description page of Project Settings.


#include "MrAussichtGlasses.h"

#include "Cyclop.h"
#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "QuestSystem.h"
#include "UQuest.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMrAussichtGlasses::AMrAussichtGlasses()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	GlassesStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassesStaticMesh"));

	SetRootComponent(CapsuleComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	GlassesStaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMrAussichtGlasses::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMrAussichtGlasses::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMrAussichtGlasses::Interact(APS1Character* Interactor)
{
	if(const ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(const UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			MyGameMode->DialogSystem->StartDialogSystem(MyGameInstance->QuestSystem->GetCurrentQuest()->GetDialog(ACyclop::StaticClass()).GetDefaultObject());

			Destroy();
		}
	}
}