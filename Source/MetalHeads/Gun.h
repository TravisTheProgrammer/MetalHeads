// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "PaperFlipbookComponent.h"
#include "Enums.h"

#include "Components/ActorComponent.h"
#include "Gun.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METALHEADS_API UGun : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGun();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/* Properties */

	// How long it takes to cycle a shot
	UPROPERTY(EditAnywhere, Category = "ShotCycle")
		float cycleSpeed = 0.3f;

	// How many bullet per shot are fired (mainly for shotgun)
	UPROPERTY(EditAnywhere, Category = "Shotgun")
		int32 bulletsPerShot = 1;

	// How many bullets are fired per shot "action" (simulate burst fire for smgs)
	UPROPERTY(EditAnywhere, Category = "Burst")
		int32 bulletsPerBurst = 6;

	// Current burst count
	UPROPERTY(EditAnywhere, Category = "Burst")
		int32 burstCount = 0;

	// Special "auto fire" cycle rate for burst fire.
	UPROPERTY(EditAnywhere, Category = "Burst")
		float burstCycleRate = 0.1f;

	// Angle increment for each successive burst shot, in degrees
	UPROPERTY(EditAnywhere, Category = "Burst")
		float burstAngleIncrement = 2.0f;

	// Last angle put in while shooting. Used as a reference for burst fire.
	UPROPERTY(EditAnywhere, Category = "Burst")
		float aimAngleOfLastShot = 0;

	// How big the bullet spawned is. To be realistic, values between 3(mm) and 10(mm) should be used.
	UPROPERTY(EditAnywhere, Category = "Physics")
		float bulletSize = 9.0f;

	// How fast the bullet is. IRL .303 enfield is ~750 m/s, while 9mm parabellum is ~370 m/s 
	// Default speed is .303
	UPROPERTY(EditAnywhere, Category = "Physics")
		float bulletSpeed = 3700.0f;

	// Maximum angle of bullet shot (so angle when firing with 0 aim time)
	UPROPERTY(EditAnywhere, Category = "Aiming")
		float maxAimAngle = 60.0f;

	// Minimum angle of bullet shot (so angle when firing at maximum aim time)
	UPROPERTY(EditAnywhere, Category = "Aiming")
		float minAimAngle = 0.0f;

	// Maximum aim time before the gun "zeroes in" (in seconds)
	UPROPERTY(EditAnywhere, Category = "Aiming")
		float maxAimTime = 3.0f;

	// How long it takes to load a fresh magazine into the gun
	UPROPERTY(EditAnywhere, Category = "Reload")
		float reloadSpeed = 4.0f;

	// How many bullets you can fire before the magazine is empty
	UPROPERTY(EditAnywhere, Category = "Reload")
		int32 magazineSize = 50;

	// How many bullets are currently in the magazine
	UPROPERTY(EditAnywhere, Category = "Reload")
		int32 remainingBullets = 50;

	// The chance that each bullet has to harm (cause status) instead of "deflecting"
	UPROPERTY(EditAnywhere, Category = "Damage")
		float harmChance = 90.0f; // from 0 to 100

	// Current state of the gun. "Ready" State means it's ready to shoot
	UPROPERTY(EditAnywhere, Category = "State")
		EGunState currentGunState = EGunState::Ready;

	/* Timers */

	FTimerHandle CycleGunHandler;
	FTimerHandle ReloadHandler;
	FTimerHandle BurstHandler;

	/* Functions */

	// Public shoot handler.
	void ShootGun(float shotAngle);

private:

	// Change State
	void ChangeGunState(EGunState newState);

	/* Timer Events */
	void GunCycleDone();
	void GunReloadDone();
	void GunBurstDone();

	// Called while gun is in burst fire state
	void BurstFire();

	// Shoot the gun. Like, for reals.
	void Fire();

};
