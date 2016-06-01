// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletCollider = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("Bullet Collider"));
	// default bullet size as a safety measure
	bulletCollider->InitSphereRadius(1);
	bulletCollider->SetSimulatePhysics(true);
	bulletCollider->BodyInstance.SetCollisionProfileName("BlockAll");
	RootComponent = bulletCollider;

	// set up visual component
	myFlipbook = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("AnimComponent"));
	myFlipbook->AttachTo(RootComponent);
	UPaperFlipbook* bulletFlip = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Art/Sprites/MH_Bullet_Flipbook.MH_Bullet_Flipbook'")));
	myFlipbook->SetFlipbook(bulletFlip);

	bulletMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Bullet Movement"));
	bulletMovement->UpdatedComponent = bulletCollider;
	bulletMovement->InitialSpeed = 3000.0f;
	bulletMovement->MaxSpeed = 3000.0f;
	bulletMovement->bRotationFollowsVelocity = true;
	bulletMovement->bShouldBounce = true;
	bulletMovement->Bounciness = 0.3f;


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UCameraComponent* mainCam = AMetalHeadsGameMode::GetMainCamera();

	// double check the pointer
	if (mainCam)
	{
		AMetalHeadsGameMode::RotateFlipbookOrtho(myFlipbook, mainCam->ComponentToWorld.Rotator());
	}
}

void ABullet::Init(FVector bulletDirection, const float& bulletRadius) 
{
	if (!bulletMovement || !bulletCollider) {
		return;
	}

	// Set our bullet size
	bulletCollider->SetSphereRadius(bulletRadius);
	bulletSize = bulletRadius;

	// Ensure normalization
	bulletDirection.Normalize();

	bulletMovement->Velocity = bulletDirection * bulletMovement->InitialSpeed;
}

