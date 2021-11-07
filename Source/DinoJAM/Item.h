// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class DINOJAM_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Overlap")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="POP UP")
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Flare")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMesh* SkeletalMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APS1Character* Interactor) override;

	virtual void UseItem()
	{
		
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Thumbnail")
	class UTexture2D* ItemThumbnail;

	bool bCanUse = true;
};
