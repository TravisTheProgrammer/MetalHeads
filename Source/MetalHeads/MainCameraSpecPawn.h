// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "MainCameraSpecPawn.generated.h"

/**
 * 
 */
UCLASS()
class METALHEADS_API AMainCameraSpecPawn : public ASpectatorPawn
{
	GENERATED_BODY()

		// Properties
public:

	AMainCameraSpecPawn(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraZoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraZoomMin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraZoomMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraMinViewDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraMaxViewDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraZoomSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraFastMoveMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float CameraScrollBounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		bool bCanMoveCamera;

private:

	float FastMoveMultiplier;	// usually x1.0 and x2.0 
	float XMovement;			// Forward / Backwards
	float YMovement;			// Left / Right
	float CurrentZoom;			// current zoom value

	// Functions
private:

	void SetupPlayerInputComponent(class UInputComponent* InputComponent);

public:

	UFUNCTION()
		void ZoomInWheel();

	UFUNCTION()
		void ZoomOutWheel();

	UFUNCTION()
		void FastMoveInput(float Direction);

	// Forward and back event
	UFUNCTION()
		void MoveCameraForwardInput(float Direction);

	// Right and left event
	UFUNCTION()
		void MoveCameraRightInput(float Direction);

	UFUNCTION()
		void AdjustZoom();

	// Tick
	UFUNCTION()
		virtual void Tick(float DeltaSeconds) override;

	/* Actual movement logic functions */
private:
	UFUNCTION()
		void MoveCameraForward(float Direction);

	UFUNCTION()
		void MoveCameraRight(float Direction);
};