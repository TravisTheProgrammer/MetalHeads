// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MetalHeads.h"
#include "MetalHeadsGameMode.h"
#include "MetalHeadsPlayerController.h"
#include "MetalHeadsCharacter.h"

AMetalHeadsGameMode::AMetalHeadsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMetalHeadsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}