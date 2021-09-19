// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DinoJAMGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StepArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("StepArrowComponent"));

	StepArrowComponent->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FQuat(FRotator(0.0, -90.0, 0.0)));

	GetMesh()->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	this->bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &APlayerCharacter::MoveSides);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Interact()
{
	if(bIsOnDialog)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());

		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(GameModeBase);

		if (MyGameMode)
		{
			MyGameMode->PlayNextDialog();
		}
	}
}

void APlayerCharacter::OnDialogFinish()
{
	bIsOnDialog = false;
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::PlayStepSound_Implementation()
{
	FVector StepLocation = StepArrowComponent->GetComponentLocation();

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(30.0);

	FHitResult OutHit;
	
	DrawDebugSphere(GetWorld(), StepLocation, CollisionShape.GetSphereRadius(), 16, FColor::Red);
	bool Success = GetWorld()->SweepSingleByChannel(OutHit, StepLocation, StepLocation, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, CollisionShape);

	if(Success)
	{
		switch (OutHit.PhysMaterial->SurfaceType)
		{
			case SurfaceType1:
				{
					if(ConcreteStepSound)
						UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteStepSound, StepLocation);
				}
			case SurfaceType2:;
			case SurfaceType3:;
			case SurfaceType4:;
			default: ;
		}
	}
}
