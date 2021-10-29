// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAMGameModeBase.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "TriggerableDialog.generated.h"

UCLASS()
class DINOJAM_API ATriggerableDialog : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerableDialog();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog System")
	TArray<TSubclassOf<class UDialogItem>> InteractableDialog;

	FOnDialogFinish OnInteractableDialogFinish;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APS1Character* Interactor) override;
};
