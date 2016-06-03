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
	
	if (FMath::RandRange(1, 20) == 20) {
		this->ShootGun(0);
	}
	// ...
}

void UGun::ShootGun(float shotAngle) {
	
	// Testing phase one: shoot straight
	FVector initDirection = this->GetOwner()->GetActorForwardVector();
	initDirection.Normalize();

	UPaperFlipbookComponent* potentialFlipbook = this->GetOwner()->FindComponentByClass<UPaperFlipbookComponent>();
	if (!potentialFlipbook) {
		return;
	}
	FVector spawnPos = potentialFlipbook->GetSocketLocation(TEXT("GunBarrel"));
	FRotator spawnRot = this->GetOwner()->GetActorRotation();

	ABullet* bullet = this->World->SpawnActor<ABullet>(ABullet::StaticClass(), spawnPos, spawnRot);
	bullet->Init(initDirection, 5);
}

