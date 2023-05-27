// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dialog.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoscaMansionOnFinishSequencer.generated.h"

UCLASS()
class DINOJAM_API AMoscaMansionOnFinishSequencer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoscaMansionOnFinishSequencer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSceneFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog to be played")
	TSubclassOf<UDialog> DialogRef;

	UFUNCTION(BlueprintCallable)
	void OnDialogFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Last intro sequence")
	ULevelSequence* LastSequence;

	UFUNCTION(BlueprintCallable)
	void OnLastSequenceFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	ACameraActor* CameraToFind;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
