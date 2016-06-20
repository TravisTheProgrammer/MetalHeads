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

#include "GameFramework/Character.h"
#include "BaseAgent.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS(Blueprintable)
class METALHEADS_API ABaseAgent : public ACharacter
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
	UFUNCTION(BlueprintCallable, Category = Aiming)
	virtual void Aim(ABaseAgent* target);

	// Increments the aim angle, using the gun for normalization.
	// Parameters are based on the chosen aim time for the agent.
	virtual void AimTick();

	// Call to stop aiming, if currently aiming. This will not trigger a shoot action.
	UFUNCTION(BlueprintCallable, Category = Aiming)
	virtual void StopAimTick();

	// Fires the gun, depending on various internal parameters (aiming, moving, etc).
	UFUNCTION(BlueprintCallable, Category = Shooting)
	virtual void Shoot();

	// Take a wound from an incoming bullet... or if you're feeling malicious.
	UFUNCTION(BlueprintCallable, Category = Hit)
	virtual void TakeWound(float woundChance, EHitLocation location);

	// Until death do us part (kill the agent). Pass in a cause of death.
	UFUNCTION(BlueprintCallable, Category = Hit)
	virtual void Die(ECauseOfDeath cod);

	// Timer event to handle bleeding per second.
	virtual void CheckBleed();

	// Event for handling hit events
	// NOTE: Had to adjust function to work around a bug...
	UFUNCTION()
	virtual void  OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

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
	//UPROPERTY(EditAnywhere)
		//UTextRenderComponent* woundText;

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

	// Aim Locations (to be set in blueprint implimentation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AimLocation)
		USceneComponent* headAimLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AimLocation)
		USceneComponent* bodyAimLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AimLocation)
		USceneComponent* legsAimLoc;

	// Our current aiming "state"
	UPROPERTY(EditAnywhere, Category = Aiming)
		EAimLocation currentAimLocation;
	
	UPROPERTY(VisibleAnywhere, Category = Aiming)
		ABaseAgent* currentTarget;

	UPROPERTY(EditAnywhere, Category = Aiming)
		float targetAimTime;

	UPROPERTY(EditAnywhere, Category = Aiming)
		float currentAimTime;

	// Spline component to render aim line
	// NOTE: Keeping around, but unlikely to be used, since I'm rendering a simple "line"!
	UPROPERTY(EditAnywhere, Category = Aiming)
		USplineComponent* aimSpline;

	// Spline mesh for drawing the aim line
	UPROPERTY(EditAnywhere, Category = Aiming)
		USplineMeshComponent* aimMesh;

	// If not none, is dead.
	UPROPERTY(EditAnywhere, Category = Status)
		ECauseOfDeath deathStatus = ECauseOfDeath::None;

	// What the agent is currently doing
	UPROPERTY(EditAnywhere, Category = State)
		EActionState currentAction;

	// TODO: See if I can rid this and use a death flipbook play length instead.
	UPROPERTY()
		float deathDelay = 0.5f;

	// Timer handlers
	FTimerHandle DeathCountdownHandler;
	FTimerHandle BleedTickPerSecondHandler;
	FTimerHandle AimingHandler;

	// Simple additional states
	
	/* Structs */

	// Status Effect Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FStatusEffect statusStruct;
	
	// Movement Data
	UPROPERTY(EditAnywhere, Category = Struct)
		FMovementStruct movementStruct;

	// Visual Component
	UPROPERTY(EditAnywhere, Category = Visuals)
		UPaperFlipbookComponent* mainFlipbook;

	private:
	void JustDie() {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("Blarg I have died"));
		Destroy();
	}

};
