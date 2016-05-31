// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MetalHeads.h"
#include "MetalHeadsGameMode.h"
#include "MainCameraController.h"
#include "MainCameraSpecPawn.h"
#include "BaseAgent.h"
#include "EngineUtils.h"

AMetalHeadsGameMode::AMetalHeadsGameMode()
{
	// use our custom PlayerController class and spec pawn
	PlayerControllerClass = AMainCameraController::StaticClass();
	DefaultPawnClass = AMainCameraSpecPawn::StaticClass();

}

void AMetalHeadsGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const world = GetWorld();
	if (world)
	{
		// Bake some default spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// NOTE: test method. remove when done
		FVector spawnPos = FVector(0, 0, 200);
		ABaseAgent* agent = world->SpawnActor<ABaseAgent>(ABaseAgent::StaticClass(), spawnPos, FRotator::ZeroRotator, SpawnParams);

	}
}

// Find the "main camera" component (the spec pawn's camera)
UCameraComponent* AMetalHeadsGameMode::GetMainCamera()
{
	for (TObjectIterator<AMainCameraSpecPawn> Iter; Iter; ++Iter)
	{
		if (Iter) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Iter->GetName());
			UCameraComponent* possibleCamera = Iter->FindComponentByClass<UCameraComponent>();
			if (possibleCamera) {
				return possibleCamera;
			}
		}
	}
	return nullptr;
	
}

void AMetalHeadsGameMode::RotateFlipbookOrtho(UPaperFlipbookComponent* flipbook, FRotator camRot)
{
	if (!flipbook) {
		return;
	}

	// Adjust for our own rotator
	FRotator flipbookRot = FRotator();
	flipbookRot.Roll = 0; // Ensure this is 0, otherwise BAD THINGS HAPPEN;
	flipbookRot.Roll = camRot.Pitch;
	flipbookRot.Yaw = camRot.Yaw + 90;

	flipbook->SetWorldRotation(flipbookRot);
}