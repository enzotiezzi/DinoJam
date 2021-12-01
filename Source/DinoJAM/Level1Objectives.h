// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Level1Objectives.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel1Objectives : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	class AObjective* KarenOutDoorStairs;

	UPROPERTY(BlueprintReadWrite)
	class AObjective* KarenIndoorPlaceBox;
};
