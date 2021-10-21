// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Engine/TriggerSphere.h"
#include "TriggerPlayPiano.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ATriggerPlayPiano : public ATriggerSphere, public IInteractable
{
	GENERATED_BODY()

public:
	ATriggerPlayPiano();
	
	virtual void Interact(APS1Character* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PianoStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundCue* Music;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	class USoundAttenuation* SoundAttenuation;

	struct FTimerHandle MusicTimerHandle;
	void OnMusicFinish();
};
