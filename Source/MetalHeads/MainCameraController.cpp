// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "BaseAgent.h"

#include "MainCameraController.h"

AMainCameraController::AMainCameraController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

void AMainCameraController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMainCameraController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMainCameraController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMainCameraController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMainCameraController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMainCameraController::MoveToTouchLocation);
}

void AMainCameraController::MoveToMouseCursor()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Click"));
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMainCameraController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMainCameraController::SetNewMoveDestination(const FVector DestLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Clack"));

	for (TObjectIterator<ABaseAgent> Iter; Iter; ++Iter)
	{
		if (Iter) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Iter->GetName());

			// TODO: Replace this with actual logic. Right now, just move everyone on Team 1 to the click location.
			if (Iter->currentTeam == ETeam::Team1) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Moving out"));
				Iter->movementStruct.currentDesination = DestLocation;
			}
		}
	}

	/*
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
	*/
}

void AMainCameraController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Boop"));
	bMoveToMouseCursor = true;
}

void AMainCameraController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Beep"));
	bMoveToMouseCursor = false;
}



