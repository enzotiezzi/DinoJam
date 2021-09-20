// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "Interactable.h"
#include "GameFramework/Character.h"
#include "Karen.generated.h"

UCLASS()
class DINOJAM_API AKaren : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKaren();
	DECLARE_DELEGATE_OneParam(FOnDialogFinish, FDialogItem);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// DIALOGS
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogBeforeLevel;
	FOnDialogFinish OnDialogBeforeLevelFinish;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogBeforeSetupPiano;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogDuringSetupPiano;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogFindHammer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogNoHammer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogFoundHammer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogBuildPiano;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogPlayPiano;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogItem> DialogLevelComplete;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void Interact(ACharacter* Interactor) override;

	void UpdateDialogAnimationOwner(TArray<FDialogItem> Dialog, ACharacter* Interactor);
};
