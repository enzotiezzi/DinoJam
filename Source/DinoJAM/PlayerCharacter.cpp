// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DinoJAMGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Interactable.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FQuat(FRotator(0.0, -90.0, 0.0)));
	GetMesh()->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleComponentEndOverlap);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	this->bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 200;
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
	else
	{
		if(CurrentInteractable)
		{
			CurrentInteractable->Interact(this);
		}
		else
		{
			FVector Start = GetActorLocation();
			FVector End = GetActorLocation() + (GetActorForwardVector() * 150.0);

			FHitResult OutHit;

			FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
			CollisionQueryParams.AddIgnoredActor(this);

			DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);
			bool Success = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Pawn, CollisionQueryParams);

			if(Success)
			{
				IInteractable* InteractableCharacter = Cast<IInteractable>(OutHit.Actor);

				if(InteractableCharacter)
				{
					InteractableCharacter->Interact(this);
				}
			}
		}
	}
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0 && bCanMove)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0 && bCanMove)
	{
		FRotator Rotation = GetController()->GetControlRotation();
		FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::PlayStepSound_Implementation()
{
	FHitResult OutHit;

	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	// DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() - FVector(0.0, 0.0, 500.0), FColor::Red, true);
	bool Success = GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), GetActorLocation() - FVector(0.0, 0.0, 500.0), ECC_Visibility, CollisionQueryParams);

	if(Success)
	{
	    if(OutHit.PhysMaterial != nullptr)
	    {
	    	USoundCue* SoundCueToBePlayed = ConcreteStepSound;
	    	
	    	switch (OutHit.PhysMaterial->SurfaceType)
	    	{
	    		case SurfaceType1:
	    			{
	    				if(ConcreteStepSound)
	    					SoundCueToBePlayed = ConcreteStepSound;
	    			}
	    		case SurfaceType2:
	    			{
	    				if(WoodenStepSound)
	    					SoundCueToBePlayed = WoodenStepSound;
	    			}
	    		case SurfaceType3:
	    			{
	    				if(DirtStepSound)
	    					SoundCueToBePlayed = DirtStepSound;
	    			}
	    		case SurfaceType4:
	    			{
	    				if(TiledStepSound)
	    					SoundCueToBePlayed = TiledStepSound;
	    			}
	    		default:
	    			if(ConcreteStepSound)
	    				SoundCueToBePlayed = ConcreteStepSound;
	    	}

	    	if(SoundCueToBePlayed)
	    		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCueToBePlayed, GetActorLocation());
	    }
	}
}

void APlayerCharacter::OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		CurrentInteractable = Interactable;

		CurrentInteractable->PreviewInteraction(this);
	}
}

void APlayerCharacter::OnCapsuleComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		CurrentInteractable = nullptr;
	}
}

