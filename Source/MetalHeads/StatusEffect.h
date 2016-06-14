// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums.h"

#include "StatusEffect.generated.h"


/**
*	This struct is used to contain wound status information.
*	It is also has convienience methods to handle blood loss, penalties, etc.
*/

USTRUCT(BlueprintType)
struct FStatusEffect
{
	GENERATED_BODY()

	// Starting health, basically. In millimeters!
	UPROPERTY()
		int32 startingOilPoints;

	// Current amount of health
	UPROPERTY()
		int32 currentOilPoints;

	// How much blood is lost per executed tick.
	UPROPERTY()
		int32 bloodLostPerTick;

	// The mighty TArray of hits. Since they can stack, we need to collect them all.
	UPROPERTY()
		TArray<EHitLocation> currentStatusEffects;

	// Constructor, with agent owner pointer ref
	FStatusEffect();

	// Add a status effect to the struct TArray, based on hit location
	void AddStatus(EHitLocation statusLocation);

	// Have the struct calculate penalties, either halfing or nulling multiplier
	// Use "bleedtick" to have bleeding occur. 
	void GetPenalties(float& outMovementPen, float& outAimPen);

	// Have the struct reduce blood per tick, based on internal parameters.
	// Call this in the agent's tick method.
	// Returns a bool to indicate if the agent has bled out.
	bool BleedTick();

	// Returns true if a bleeding status was found, otherwise false.
	bool IsBleeding();

};