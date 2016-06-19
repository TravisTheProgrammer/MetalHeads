// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "StatusEffect.h"

FStatusEffect::FStatusEffect()
{
	startingOilPoints = 3000; //ml
	currentOilPoints = startingOilPoints;
	// The TArray starts empty to imply no status effects

	// Edit blood loss per tick here.
	oilLostPerTick = 1; // multiplied by bleedPointCount later.
	bleedPointCount = 0;
	torsoBonus = 5;

	statusBitMask = 0;
}

void FStatusEffect::AddStatus(EHitLocation statusLocation) 
{
	if (statusLocation == EHitLocation::Head) {
		// ... hmm, this shouldn't happen. BaseAgent should kill it on the spot 
		// Let's get rid of all blood in case we somehow have this happen.
		// This kills the Agent.
		currentOilPoints = 0;
	}else{
		currentStatusEffects.Add(statusLocation);
		UpdateStatus();
	}
}

void FStatusEffect::UpdateStatus() 
{
	// count up hits
	int32 leftLeg = 0;
	int32 rightLeg = 0;
	int32 leftArm = 0;
	int32 rightArm = 0;
	int32 torso = 0;

	// NOTE: Could have these counts as properties for UI, to show how mangled an agent is...

	for (EHitLocation hit : currentStatusEffects) {
		switch (hit)
		{
		case EHitLocation::LeftArm:
			leftArm++;
			break;
		case EHitLocation::RightArm:
			rightArm++;
			break;
		case EHitLocation::LeftLeg:
			leftLeg++;
			break;
		case EHitLocation::RightLeg:
			rightLeg++;
			break;
		case EHitLocation::Torso:
			torso++;
			break;
		default:
			break;
		}
	}

	// handle bleed count first.
	bleedPointCount = leftLeg + rightLeg + leftArm + rightArm + (torso * torsoBonus);

	// flip the bitmask depending on our count.
	if (leftLeg > 0 && rightLeg > 0) {
		statusBitMask |= (uint8) EStatusEffectsFlags::NoLegs;
	} else if (leftLeg > 0 || rightLeg > 0) {
		statusBitMask |= (uint8)EStatusEffectsFlags::CrippledLeg;
	}

	if (leftArm > 0 && rightArm > 0) {
		statusBitMask |= (uint8)EStatusEffectsFlags::NoArms;
	} else if (leftArm > 0 || rightArm > 0) {
		statusBitMask |= (uint8)EStatusEffectsFlags::CrippledArm;
	}

	if (torso > 0) {
		statusBitMask |= (uint8)EStatusEffectsFlags::Bleeding;
	}

	// TODO: better placement of this update...
	GetPenalties(movementPenalty, aimPenalty);
}

void FStatusEffect::GetPenalties(float& outMovementPen, float& outAimPen)
{
	if(statusBitMask & (uint8) EStatusEffectsFlags::NoArms){
		outMovementPen = 0;
	} else if (statusBitMask & (uint8)EStatusEffectsFlags::CrippledArm) {
		outMovementPen = 0.5f;
	}
	
	if (statusBitMask & (uint8)EStatusEffectsFlags::NoLegs) {
		outAimPen = 0;
	} else if (statusBitMask & (uint8) EStatusEffectsFlags::CrippledLeg) {
		outAimPen = 0.5f;
	}
	
}

bool FStatusEffect::IsBleeding()
{
	if (bleedPointCount > 0) {
		return true;
	}
	return false;
}

bool FStatusEffect::BleedTick()
{
	// Do nothing if not bleeding.
	if (!IsBleeding()) {
		return false;
	}

	currentOilPoints -= bleedPointCount;
	// NOTE: Additional bleeding logic could be inserted here.
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(currentOilPoints));

	if (currentOilPoints < 1) {
		return true;
	}

	return false;
}

