// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DinoJAM/PS1Character.h"
#include "BookWorm.generated.h"

/**
 * 
 */
UCLASS()
class DINOJAM_API ABookWorm : public APS1Character
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	bool bCanMove = false;

	UFUNCTION(BlueprintCallable)
	void Dance();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
	UAnimMontage* HappyAnimation;
};
