// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Game Mode enums

UENUM(BlueprintType)
enum class ETeam : uint8
{
	None,
	Team1,
	Team2,
	COUNT
};

// Base Agent enums

UENUM(BlueprintType)
enum class EAimLocation : uint8
{
	None,
	Head,
	Body,
	Legs,
	COUNT
};

UENUM(BlueprintType)
enum class EHitLocation : uint8
{
	None,
	Head,
	LeftArm,
	RightArm,
	Torso,
	LeftLeg,
	RightLeg,
	COUNT
};

UENUM(BlueprintType)
enum class ECauseOfDeath : uint8
{
	None, // Died from NOTHING... you should know why none is the default by now...
	Headshot,
	Hypooleum,
	// Would be nice to expand death causes... shock from too many wounds would be neat.
	COUNT
};

// NOTE: This does not include movement state. These are action states.
UENUM(BlueprintType)
enum class EActionState : uint8
{
	None,
	Idle,
	Aiming,
	Shooting,
	COUNT
};

// Gun enums

UENUM(BlueprintType)
enum class EGunState : uint8
{
	None,
	Ready,
	Cycling,
	BurstFire,
	Reloading,
	Shooting,
	COUNT
};

// Status Effect bitmask
UENUM(BlueprintType)
enum class EStatusEffectsFlags
{
	None = 0x00, 
	Bleeding = 0x01,
	CrippledArm = 0x02, // take care not to have a "crippled" and "no" state at the same time.
	NoArms = 0x04,		// or rather, have logic where that overlap is a problem!
	CrippledLeg = 0x08,
	NoLegs = 0x16
};

ENUM_CLASS_FLAGS(EStatusEffectsFlags)

// Movement enums

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	None, // None is different from Idle, in that None implies movement is unset entirely
	Idle,
	Walking,
	Running,
	COUNT
};


/**
 * 
 */
class METALHEADS_API Enums
{
public:
	Enums();
	~Enums();
};
