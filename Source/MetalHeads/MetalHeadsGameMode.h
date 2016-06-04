// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "PaperFlipbookComponent.h"

#include "GameFramework/GameMode.h"
#include "MetalHeadsGameMode.generated.h"

/**
 *  Enum used for various possible teams.
 */
UENUM(BlueprintType)
enum class ETeam : uint8
{
	None,
	Team1,
	Team2,
	COUNT
};

UCLASS(minimalapi)
class AMetalHeadsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMetalHeadsGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns the main camera (first spawned spec pawn)
	static UCameraComponent* GetMainCamera();

	// Rotates a paper2D component to face the camera
	static void RotateFlipbookOrtho(UPaperFlipbookComponent* flipbook, FRotator camRot);

	// Convienience method to load objects
	template <typename ObjClass>
	static ObjClass* LoadObjFromPath(const FName& Path) {
		if (Path == NAME_None) return NULL;

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}


};



