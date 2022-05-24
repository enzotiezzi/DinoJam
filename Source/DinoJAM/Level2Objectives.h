// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <DinoJAM/Objective.h>
#include "Level2Objectives.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ULevel2Objectives : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AObjective* PlaceMrAussichtPackObjective;
};
