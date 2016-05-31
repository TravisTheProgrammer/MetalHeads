// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY(EditAnywhere)
		float cycleSpeed;

	// How long it takes to load a fresh magazine into the gun
	UPROPERTY(EditAnywhere)
		float reloadSpeed;

	// How many bullet per shot are fired (mainly for shotgun)
	UPROPERTY(EditAnywhere)
		int32 bulletsPerShot;

	// How many bullets are fired per shot "action" (simulate burst fire for smgs)
	UPROPERTY(EditAnywhere)
		int32 bulletsPerBurst;

	// How big the bullet spawned is. To be realistic, values between 0.3 and 1 should be used.
	UPROPERTY(EditAnywhere)
		float bulletSize;

	// How many bullets you can fire before the magazine is empty
	UPROPERTY(EditAnywhere)
		int32 magazineSize;

	// The chance that each bullet has to harm (cause status) instead of "deflecting"
	UPROPERTY(EditAnywhere)
		float harmChance; // from 0 to 100

	// Is the gun shooting? The gun can't do anything else while shooting!
	UPROPERTY(EditAnywhere)
		bool isShooting;

	/* Functions */

	/* Shoot the gun. Feed it the desired spread angle, and it will spawn bullets 
	according to the gun's stats */
	void ShootGun(float shotAngle);
};
