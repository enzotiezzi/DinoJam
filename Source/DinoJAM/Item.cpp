// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "DinoJAMGameModeBase.h"
#include "InventorySystem.h"
#include "MyGameInstance.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Game/itens/ItemFlare/Item_Flare_Object"));
	SkeletalMesh = SkeletalMeshFinder.Object;
	
	SetRootComponent(SphereComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	
	SphereComponent->SetSphereRadius(64.0);
	
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	SkeletalMeshComponent->SetRelativeLocationAndRotation(FVector(0, 0, 20), FQuat(FRotator(0, 0, -90)));
	SkeletalMeshComponent->SetWorldScale3D(FVector(.1, .1, .1));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact(APS1Character* Interactor)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		if(UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			MyGameInstance->InventorySystem->AddItem(this);
			MyGameInstance->InventorySystem->ShowItemPopUp(ItemThumbnail, Description);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), MyGameInstance->PickUpItemSound, GetActorLocation(), GetActorRotation());
			
			SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SkeletalMeshComponent->DestroyComponent();
		}
	}
}
