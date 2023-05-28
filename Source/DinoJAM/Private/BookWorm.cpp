// Fill out your copyright notice in the Description page of Project Settings.


#include "BookWorm.h"

void ABookWorm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bCanMove)
	{
		AddMovementInput(GetActorForwardVector(), .1);
	}
}

void ABookWorm::Dance()
{
	if(HappyAnimation) PlayAnimMontage(HappyAnimation);
}
