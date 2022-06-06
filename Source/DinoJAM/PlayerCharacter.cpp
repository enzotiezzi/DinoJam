// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DialogSystem.h"
#include "DinoJAMGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Interactable.h"
#include "InventorySystem.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
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
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		MyGameInstance->CurrentPlayerCharacter = this;
	}
	
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
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::PauseGame);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);
	
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
			MyGameMode->DialogSystem->PlayNextDialog();
		}
	}
	else
	{
		if(bCanInteract)
		{
			if(CurrentInteractable)
			{
				FRotator AmountNeededToLookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Cast<AActor>(CurrentInteractable)->GetActorLocation());
				AmountNeededToLookAt.Pitch = 0;
				AmountNeededToLookAt.Roll = 0;
			
				SetActorRelativeRotation(FQuat(AmountNeededToLookAt));
			
				CurrentInteractable->Interact(this);
			}
			else 
			{
				FHitResult OutHit;

				DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 25), FColor::Red, false, .5);

				bool Success = GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 25), ECC_Visibility);

				if (Success) 
				{
					IInteractable* OtherInteractable = Cast<IInteractable>(OutHit.Actor);

					if (OtherInteractable)
					{
						CurrentInteractable = OtherInteractable;

						FRotator AmountNeededToLookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Cast<AActor>(CurrentInteractable)->GetActorLocation());
						AmountNeededToLookAt.Pitch = 0;
						AmountNeededToLookAt.Roll = 0;

						SetActorRelativeRotation(FQuat(AmountNeededToLookAt));

						CurrentInteractable->Interact(this);
					}
				}
			}
		}
	}
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0 && bCanMove)
	{
		FVector Direction = GetActorForwardVector();

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0 && bCanMove)
	{
		AddActorWorldRotation(FQuat(FRotator(0, AxisValue * TurnSpeed, 0)));
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
	    			if(ConcreteStepSound)
	    				SoundCueToBePlayed = ConcreteStepSound;
	    		break;
	    		
	    		case SurfaceType2:
	    			if(WoodenStepSound)
	    				SoundCueToBePlayed = WoodenStepSound;
	    		break;
	    		
	    		case SurfaceType3:
	    			if(DirtStepSound)
	    				SoundCueToBePlayed = DirtStepSound;
	    		break;
	    		
	    		case SurfaceType4:
	    			if(TiledStepSound)
	    				SoundCueToBePlayed = TiledStepSound;
	    		break;
	    		
	    		default:
	    			if(ConcreteStepSound)
	    				SoundCueToBePlayed = ConcreteStepSound;
	    	}
	    	
	    	if(SoundCueToBePlayed)
	    		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCueToBePlayed, GetActorLocation(), FRotator::ZeroRotator,1, 1, 0, StepSoundAttenuation);
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

void APlayerCharacter::PauseGame()
{
	if(bCanMove)
	{
		ADinoJAMGameModeBase* MyGameMode = Cast<ADinoJAMGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if(MyGameMode)
		{
			MyGameMode->PauseGame();
		}
	}
}

void APlayerCharacter::StartWavingAnimationMontage()
{
	if(WavingMontage)
		PlayAnimMontage(WavingMontage);
}

void APlayerCharacter::StartBuildAnimation()
{
	if(BuildAnimation)
		PlayAnimMontage(BuildAnimation);
}

void APlayerCharacter::OpenInventory()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(MyGameInstance)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if(PlayerController)
		{
				if(!MyGameInstance->InventorySystem->IsOpened())
				MyGameInstance->InventorySystem->ShowInventory();
			else
				MyGameInstance->InventorySystem->HideInventory();
		}
	}
}
