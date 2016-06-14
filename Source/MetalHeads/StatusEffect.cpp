// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "StatusEffect.h"

FStatusEffect::FStatusEffect()
{
	startingOilPoints = 3000; //ml
	currentOilPoints = startingOilPoints;
	// The TArray starts empty to imply no status effects

	// Edit blood loss per tick here.
	bloodLostPerTick = 2;
}

void FStatusEffect::AddStatus(EHitLocation statusLocation) 
{
	if (statusLocation == EHitLocation::Head) {
		// ... hmm, this shouldn't happen. BaseAgent should kill it on the spot 
		// Let's get rid of all blood in case we somehow have this happen.
		currentOilPoints = 0;
	}else{
		currentStatusEffects.Add(statusLocation);
	}
}

void FStatusEffect::GetPenalties(float& outMovementPen, float& outAimPen)
{
	for (EHitLocation hit : currentStatusEffects) {

	}
}
