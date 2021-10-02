// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnStart() override;

	//////////////////////////////////////////////
	///
	/// CHARACTER REFERENCES
	///
	//////////////////////////////////////////////
	UPROPERTY()
	class APlayerCharacter* CurrentPlayerCharacter;

	UPROPERTY()
	class APS1Character* CurrentNPC;

	//////////////////////////////////////////////
	///
	/// QUEST STUFF
	///
	//////////////////////////////////////////////
	void StartQuest(class UQuest* Quest);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest")
	TSubclassOf<class UQuest> CurrentQuest;
	
	UPROPERTY()
	class UQuest* qCurrentQuest;

	///////////////////////////////////////////////////
	///
	/// GENERAL SOUNDS
	///
	///////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sounds")
	class USoundCue* PickUpItemSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sounds")
	class USoundCue* DropItemSound;

	/////////////////////////////////////////////
	///
	/// LEVEL 1 STUFF
	///
	/////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, Category="Level 1")
	class UStaticMeshComponent* PianoBoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Level 1")
	class UStaticMesh* PianoStaticMesh;

	UPROPERTY()
	class ATriggerPlacePianoBox* TriggerPlacePianoBox;
};
