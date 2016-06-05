// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "MovementStruct.h"

FMovementStruct::FMovementStruct()
{
	// set defaults
	currentDesination = FVector::ZeroVector;
	defaultMoverate = 2.0f;
	currentMoverate = defaultMoverate;
	currentMovementState = EMovementState::Idle;
}

