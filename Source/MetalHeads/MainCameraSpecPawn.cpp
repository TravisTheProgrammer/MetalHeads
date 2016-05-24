// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "MainCameraSpecPawn.h"

AMainCameraSpecPawn::AMainCameraSpecPawn(const FObjectInitializer& ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
	bAddDefaultMovementBindings = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraZoom = 7500.0f;
	CameraZoomMin = 200.0f;
	CameraZoomMax = 7500.0f;
	CameraMinViewDistance = 0;
	CameraMaxViewDistance = 100000.0f;

	CameraZoomSpeed = 200.0f;
	CameraMovementSpeed = 3000.0f;
	CameraFastMoveMultiplier = 2.0f;
	CameraScrollBounds = 25.0f;

	bCanMoveCamera = true;

	// Setup Camera
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Main Camera"));
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = CameraZoomMax;
	CameraComponent->OrthoNearClipPlane = CameraMinViewDistance;
	CameraComponent->OrthoFarClipPlane = CameraMaxViewDistance;

	CameraComponent->AttachParent = GetRootComponent();
	CameraComponent->bUsePawnControlRotation = false;
	AdjustZoom();

	FVector spawnLoc = FVector(0, 0, 2000);							// Default camera spawn position.
	FRotator spawnRot = FRotator(-45.0f, 225.0f, 0);	// Default camera spawn rotation.

	SetActorLocation(spawnLoc);
	SetActorRotation(spawnRot);
}

void AMainCameraSpecPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	check(InputComponent);

	Super::SetupPlayerInputComponent(InputComponent);

	// Zoom in / out
	InputComponent->BindAction("ZoomOutWheel", IE_Pressed, this, &AMainCameraSpecPawn::ZoomOutWheel);
	InputComponent->BindAction("ZoomInWheel", IE_Pressed, this, &AMainCameraSpecPawn::ZoomInWheel);

	// Movement
	InputComponent->BindAxis("MoveForward", this, &AMainCameraSpecPawn::MoveCameraForwardInput);
	InputComponent->BindAxis("MoveRight", this, &AMainCameraSpecPawn::MoveCameraRightInput);

	// Move fast
	InputComponent->BindAxis("FastMove", this, &AMainCameraSpecPawn::FastMoveInput);
}

void AMainCameraSpecPawn::ZoomInWheel() {
	if (!bCanMoveCamera) return;

	CameraZoom -= CameraZoomSpeed * FastMoveMultiplier;
	CameraZoom = FMath::Clamp(CameraZoom, CameraZoomMin, CameraZoomMax);

	AdjustZoom();
}

void AMainCameraSpecPawn::ZoomOutWheel() {
	if (!bCanMoveCamera) return;

	CameraZoom += CameraZoomSpeed * FastMoveMultiplier;
	CameraZoom = FMath::Clamp(CameraZoom, CameraZoomMin, CameraZoomMax);

	AdjustZoom();
}

void AMainCameraSpecPawn::AdjustZoom() {
	CameraComponent->OrthoWidth = CameraZoom;
}

void AMainCameraSpecPawn::FastMoveInput(float Direction) {
	if (!bCanMoveCamera)	return;

	FastMoveMultiplier = FMath::Abs(Direction) * CameraFastMoveMultiplier;

	if (FastMoveMultiplier < 1.0f) {
		FastMoveMultiplier = 1.0f;
	}

}

void AMainCameraSpecPawn::MoveCameraForwardInput(float Direction) {
	if (!bCanMoveCamera) return;

	XMovement = Direction;

}

void AMainCameraSpecPawn::MoveCameraRightInput(float Direction) {
	if (!bCanMoveCamera) return;

	YMovement = Direction;

}

void AMainCameraSpecPawn::MoveCameraForward(float Direction) {
	float MovementValue = Direction * CameraMovementSpeed;
	FVector NewLocation = GetActorLocation() + FVector(MovementValue, MovementValue, 0);

	SetActorLocation(NewLocation);
}

void AMainCameraSpecPawn::MoveCameraRight(float Direction) {
	float MovementValue = Direction * CameraMovementSpeed;
	FVector NewLocation = GetActorLocation() + FVector(-MovementValue, MovementValue, 0);

	SetActorLocation(NewLocation);
}

void AMainCameraSpecPawn::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	FVector2D MousePosition;
	FVector2D ViewportSize;

	UGameViewportClient* GameViewport = GEngine->GameViewport;

	check(GameViewport);
	GameViewport->GetViewportSize(ViewportSize);

	// Check if input is detectable
	if (GameViewport->IsFocused(GameViewport->Viewport) &&
		GameViewport->GetMousePosition(MousePosition) &&
		bCanMoveCamera) {

		// Edge of screen movement
		if (MousePosition.X < CameraScrollBounds) {
			YMovement = -1.0f;
		} else if (ViewportSize.X - MousePosition.X < CameraScrollBounds) {
			YMovement = 1.0f;
		}

		if (MousePosition.Y < CameraScrollBounds) {
			XMovement = 1.0f;
		}
		else if (ViewportSize.Y - MousePosition.Y < CameraScrollBounds) {
			XMovement = -1.0f;
		}

		// movement
		MoveCameraForward(XMovement * FastMoveMultiplier * DeltaSeconds);
		MoveCameraRight(YMovement * FastMoveMultiplier * DeltaSeconds);

	}
	
}