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
		int32 oilLostPerTick;

	// Count of how many "bleeders" there are (5 count for torso, 1 for limbs)
	UPROPERTY()
		int32 bleedPointCount;

	// NO MAGIC NUMBERS. Also, this is the worst kind of bonus...
	UPROPERTY()
		int32 torsoBonus;

	// The mighty TArray of hits. Since they can stack, we need to collect them all.
	UPROPERTY()
		TArray<EHitLocation> currentStatusEffects;

	// Bit mask for status effects
	UPROPERTY()
		uint8 statusBitMask;

	// Multiplier from 1 to 0 to affect movement speed.
	UPROPERTY()
		float movementPenalty;

	// Multipler from 1 to 0 to affect aim penalty (slowing aiming down)
	UPROPERTY()
		float aimPenalty;

	// Constructor
	FStatusEffect();

	// Add a status effect to the struct TArray, based on hit location
	void AddStatus(EHitLocation statusLocation);

	// Used to update bleeding and the status bitmask
	void UpdateStatus();

	// Have the struct calculate penalties, either halfing or nulling multiplier
	// Use "bleedtick" to have bleeding occur. 
	void GetPenalties(float& outMovementPen, float& outAimPen);

	// Have the struct reduce blood per tick, based on internal parameters.
	// Call on a 1 second interval, since the scale is ml/s
	// Returns a bool to indicate if the agent has bled out.
	bool BleedTick();

	// Returns true if a bleeding status was found, otherwise false.
	bool IsBleeding();

	// NOTE: No method to clear bitmasks, because I don't plan healing... could though.

};