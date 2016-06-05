// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "StatusEffect.h"

FStatusEffect::FStatusEffect()
{
	startingOilPoints = 3000; //ml
	currentOilPoints = startingOilPoints;
	// The TArray starts empty to imply no status effects
}

