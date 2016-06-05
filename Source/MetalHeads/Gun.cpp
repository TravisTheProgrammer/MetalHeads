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
	
	FVector initDirection = this->GetOwner()->GetActorForwardVector();
	initDirection.Normalize();

	FVector initImpulseDir = FMath::VRandCone(initDirection, FMath::DegreesToRadians(shotAngle));

	UPaperFlipbookComponent* potentialFlipbook = this->GetOwner()->FindComponentByClass<UPaperFlipbookComponent>();
	if (!potentialFlipbook) {
		return;
	}
	FVector spawnPos = potentialFlipbook->GetSocketLocation(TEXT("GunBarrel"));
	FRotator spawnRot = this->GetOwner()->GetActorRotation();

	ABullet* bullet = this->World->SpawnActor<ABullet>(ABullet::StaticClass(), spawnPos, spawnRot);
	bullet->Init(initImpulseDir, bulletSize, bulletSpeed);
}

