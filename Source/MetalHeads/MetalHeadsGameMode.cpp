// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MetalHeads.h"
#include "MetalHeadsGameMode.h"
#include "MainCameraController.h"
#include "MainCameraSpecPawn.h"

AMetalHeadsGameMode::AMetalHeadsGameMode()
{
	// use our custom PlayerController class and spec pawn
	PlayerControllerClass = AMainCameraController::StaticClass();
	DefaultPawnClass = AMainCameraSpecPawn::StaticClass();

}