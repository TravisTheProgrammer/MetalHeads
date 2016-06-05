// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MovementStruct.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	None, // None is different from Idle, in that None implies movement is unset entirely
	Idle,
	Walking,
	Running,
	COUNT
};

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
