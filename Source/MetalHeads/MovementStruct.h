// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums.h"

#include "MovementStruct.generated.h"

class ABaseAgent;

/**
 * 
 */


USTRUCT(BlueprintType)
struct FMovementStruct
{
	GENERATED_BODY()

	// Target desination that nav agent will go to
	UPROPERTY()
		FVector currentDesination;

	// How far the agent should be able to "walk" in a second, default 2 m/s
	UPROPERTY()
		float defaultMoverate;

	// Current moverate, potentially adjusted for leg damage, etc
	UPROPERTY()
		float currentMoverate;

	// The current movement state. Defaults to "Idle"
	UPROPERTY()
		EMovementState currentMovementState;

	// Constructor
	FMovementStruct();

	// Placeholder for interal data methods / get-sets
};
