// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level1Objectives.h"
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
	UPROPERTY(BlueprintReadWrite, Category="Quest System")
	class UQuestSystem* QuestSystem; 

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Level 1")
	class UStaticMesh* PianoStaticMesh;

	UPROPERTY()
	class ATriggerPlacePianoBox* TriggerPlacePianoBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Piano")
	TSubclassOf<class ATriggerPlayPiano> TriggerPlayPiano;

	////////////////////////////////////////////
	///
	/// INVENTORY
	///
	////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite)
	class UInventorySystem* InventorySystem;

	/////////////////////////////////////////////
	///
	/// OBJECTIVES
	///
	/////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite)
	ULevel1Objectives* Level1Objectives;

protected:
	///////////////////////////////////////////////
	///
	/// INVENTORY
	///
	///////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory")
	TSubclassOf<class UInventorySystem> InventorySystemReference;

	///////////////////////////////////////////////
	///
	/// QUEST SYSTEM
	///
	///////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest System")
	class TSubclassOf<class UQuestSystem> QuestSystemReference;
};