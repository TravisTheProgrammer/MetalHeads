// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "Gun.h"


// Sets default values for this component's properties
UGun::UGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGun::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	// ...
}

void UGun::ShootGun(float shotAngle) {

	// Check if we can shoot the gun.
	if (currentGunState != EGunState::Ready) {
		return;
	}

	currentGunState = EGunState::Shooting;

	aimAngleOfLastShot = shotAngle;
	
	if (bulletsPerBurst > 1) {
		ChangeGunState(EGunState::BurstFire);
		return;
	}
	else {
		Fire();
	}

	if (remainingBullets <= 0) {
		ChangeGunState(EGunState::Reloading);
	}
	else {
		ChangeGunState(EGunState::Cycling);
	}
}

void UGun::ChangeGunState(EGunState newState) {
	// Make sure all timers are reset before switching state
	this->World->GetTimerManager().ClearAllTimersForObject(this);

	switch (newState) {
	case EGunState::Reloading:
		currentGunState = EGunState::Reloading;
		this->World->GetTimerManager().SetTimer(ReloadHandler, this, &UGun::GunReloadDone, reloadSpeed, false);
		break;
	case EGunState::Cycling:
		currentGunState = EGunState::Cycling;
		this->World->GetTimerManager().SetTimer(CycleGunHandler, this, &UGun::GunCycleDone, cycleSpeed, false);
		break;
	case EGunState::BurstFire:
		currentGunState = EGunState::BurstFire;
		// load up a burst, and get firin'
		burstCount = bulletsPerBurst;
		this->World->GetTimerManager().SetTimer(BurstHandler, this, &UGun::BurstFire, cycleSpeed, false);
		break;
	default:
		currentGunState = EGunState::Ready;
		break;
	}

	//GetWorld()->GetTimerManager().SetTimer(this, &UGun::GunCycleDone, cycleSpeed, false);
}

void UGun::GunReloadDone() {
	remainingBullets = magazineSize;
	ChangeGunState(EGunState::Ready);
}

void UGun::GunCycleDone() {
	// Not much logic needed here, eh?
	ChangeGunState(EGunState::Ready);
}

void UGun::BurstFire() {
	if (currentGunState != EGunState::BurstFire) {
		return;
	}
	// Start off by firing the gun.
	Fire();
	aimAngleOfLastShot += burstAngleIncrement;
	burstCount--;

	if (remainingBullets <= 0) {
		ChangeGunState(EGunState::Reloading);
	}else{
		if (burstCount <= 0) {
			ChangeGunState(EGunState::Ready);
		}else{
			this->World->GetTimerManager().SetTimer(BurstHandler, this, &UGun::BurstFire, burstCycleRate, false);
		}
	}
}

void UGun::Fire() {
	FVector initDirection = this->GetOwner()->GetActorForwardVector();
	initDirection.Normalize();

	UPaperFlipbookComponent* potentialFlipbook = this->GetOwner()->FindComponentByClass<UPaperFlipbookComponent>();
	if (!potentialFlipbook) {
		return;
	}

	for (int i = 0; i < bulletsPerShot; i++) {

		// Spread the angle depending on the deviation angle provided
		// NOTE: Lerp from min to max later, instead of taking raw angle
		// Perhaps add a raw angle version as an overload?
		FVector initImpulseDir = FMath::VRandCone(initDirection, FMath::DegreesToRadians(aimAngleOfLastShot));


		FVector spawnPos = potentialFlipbook->GetSocketLocation(TEXT("GunBarrel"));
		FRotator spawnRot = this->GetOwner()->GetActorRotation();


		ABullet* bullet = this->World->SpawnActor<ABullet>(ABullet::StaticClass(), spawnPos, spawnRot);
		bullet->Init(initImpulseDir, bulletSize, harmChance, bulletSpeed);
	}

	remainingBullets--;
}