// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Item.h"
#include "ItemSlot.h"
#include "GameFramework/Actor.h"
#include "PianoBox.generated.h"

UCLASS()
class DINOJAM_API APianoBox : public AItem, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APianoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class UStaticMeshComponent* PianoBoxComponent;

	struct FTimerHandle DelayUntilAddItem;

	void AddItemToInventory();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ACharacter* Interactor) override;

	virtual void UseItem() override;
};
