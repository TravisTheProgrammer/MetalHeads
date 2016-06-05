// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "StatusEffect.generated.h"

/**
*
*/

UENUM(BlueprintType)
enum class EStatusEffects : uint8
{
	None, // Only here has a coding practice, don't use it; empty "currentStatusEffects" implies none
	Bleeding,
	CrippledArm,
	CrippledLeg,
	COUNT
};

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

	// The mighty TArray of states. Since effects can stack, we need to track every one
	UPROPERTY()
		TArray<EStatusEffects> currentStatusEffects;

	// Constructor
	FStatusEffect();

	// Placeholder for interal data methods / get-sets
};