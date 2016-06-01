// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MetalHeadsGameMode.h"
#include "PaperFlipbookComponent.h"
#include "Gun.h"

// Included structs
#include "MovementStruct.h"
#include "StatusEffect.h"

#include "GameFramework/Pawn.h"
#include "BaseAgent.generated.h"

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

UCLASS()
class METALHEADS_API ABaseAgent : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseAgent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Tells the agent to enter the aim state.
	virtual void Aim(ABaseAgent* target);

	// Fires the gun, depending on various parameters (aiming, moving, etc).
	virtual void Shoot();

	// Event for handling hit events
	virtual void  ABaseAgent::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Placeholder for "take hit" functions

	/* Properties */
public:

	// Root component
	UPROPERTY(EditAnywhere)
		USceneComponent* visibleRoot;

	UPROPERTY(EditAnywhere)
		ETeam currentTeam;

	// Gun Actor Component, handles all gun logic
	UPROPERTY(EditAnywhere)
		UGun* myGun;

	// Body colliders
	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* headBox;

	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* torsoBox;

	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* leftArmBox;

	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* rightArmBox;

	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* leftLegBox;

	UPROPERTY(EditAnywhere, Category = Hitboxes)
		UBoxComponent* rightLegBox;

	// Our current aiming "state"
	UPROPERTY(EditAnywhere, Category = Aiming)
		EAimLocation currentAimLocation;
	
	UPROPERTY(VisibleAnywhere, Category = Aiming)
		ABaseAgent* currentTarget;

	UPROPERTY(EditAnywhere, Category = Aiming)
		float aimTime;
	
	/* Structs */
	
	// Movement Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FMovementStruct movementStruct;

	// Status Effect Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FStatusEffect statusStruct;

	UPROPERTY(EditAnywhere, Category = Visuals)
		UPaperFlipbookComponent* mainFlipbook;

	// AI Controller / Nav Agent placeholder

};
