// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MetalHeadsGameMode.h"
#include "AgentController.h"
#include "PaperFlipbookComponent.h"
#include "Gun.h"
#include "Enums.h"

// structs
#include "StatusEffect.h"
#include "MovementStruct.h"

#include "GameFramework/Pawn.h"
#include "BaseAgent.generated.h"

UCLASS(Blueprintable)
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

	// Take a wound from an incoming bullet... or if you're feeling malicious.
	virtual void TakeWound(float woundChance, EHitLocation location);

	// Until death do us part (kill the agent). Pass in a cause of death.
	virtual void Die(ECauseOfDeath cod);

	// Event for handling hit events
	// NOTE: Had to adjust function to work around a bug...
	UFUNCTION()
	virtual void  OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Placeholder for "take hit" functions

	/* Properties */
public:

	UPROPERTY(EditAnywhere)
		ETeam currentTeam;

	// Gun Actor Component, handles all gun logic
	UPROPERTY(EditAnywhere)
		UGun* myGun;

	// Placeholder info obj text
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* statusText;
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* woundText;

	// Body colliders
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* headBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* torsoBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* leftArmBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* rightArmBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* leftLegBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hitboxes)
		UBoxComponent* rightLegBox;

	// Our current aiming "state"
	UPROPERTY(EditAnywhere, Category = Aiming)
		EAimLocation currentAimLocation;
	
	UPROPERTY(VisibleAnywhere, Category = Aiming)
		ABaseAgent* currentTarget;

	UPROPERTY(EditAnywhere, Category = Aiming)
		float aimTime;

	// If not none, is dead.
	UPROPERTY(EditAnywhere, Category = Status)
		ECauseOfDeath deathStatus = ECauseOfDeath::None;

	// Simple additional states
	
	/* Structs */

	// Status Effect Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FStatusEffect statusStruct;
	
	// Movement Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FMovementStruct movementStruct;

	UPROPERTY(EditAnywhere, Category = Visuals)
		UPaperFlipbookComponent* mainFlipbook;

};
