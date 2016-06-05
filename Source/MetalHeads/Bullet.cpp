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
	bulletCollider->InitSphereRadius(0.5f);
	//bulletCollider->SetSimulatePhysics(true);   // THIS WAS A GOD DAMN TRAP FOR PROJECTILE MOVEMENT
	bulletCollider->SetNotifyRigidBodyCollision(true);
	bulletCollider->BodyInstance.SetCollisionProfileName("Bullet");
	// bulletCollider->BodyInstance.SetMassScale(0.01f);
	// NOTE: Would like to simulate SOME gravity in the future
	//bulletCollider->SetEnableGravity(false);
	bulletCollider->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	RootComponent = bulletCollider;

	// set up visual component
	myFlipbook = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("AnimComponent"));
	myFlipbook->AttachTo(RootComponent);
	UPaperFlipbook* bulletFlip = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Art/Sprites/MH_Bullet_Flipbook.MH_Bullet_Flipbook'")));
	myFlipbook->SetFlipbook(bulletFlip);

	bulletMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Bullet Movement"));
	bulletMovement->InitialSpeed = 120.0f;
	bulletMovement->UpdatedComponent = bulletCollider;
	bulletMovement->bRotationFollowsVelocity = true;
	bulletMovement->bShouldBounce = true;
	bulletMovement->Bounciness = 0.3f;

	// Bullet max lifespan, in case it flies into the sky or something
	InitialLifeSpan = 15.0f;

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

	if (bulletMovement->Velocity.Size() < 100.0f) {
		Destroy();
	}

	UCameraComponent* mainCam = AMetalHeadsGameMode::GetMainCamera();

	// double check the pointer
	if (mainCam)
	{
		AMetalHeadsGameMode::RotateFlipbookOrtho(myFlipbook, mainCam->ComponentToWorld.Rotator());
	}
}

void ABullet::Init(FVector bulletDirection, const float& bulletRadius, const float& bulletVelocity)
{
	if (!bulletMovement || !bulletCollider) {
		return;
	}
	float bulletSize = bulletRadius * 0.1f;

	// Set our bullet size
	bulletCollider->SetSphereRadius(bulletSize);
	myFlipbook->RelativeScale3D = FVector(1, 1, 1) * (bulletSize);

	// Ensure normalization
	bulletDirection.Normalize();

	bulletMovement->Velocity = bulletDirection * bulletVelocity;
}

void ABullet::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		// placeholder for hit logic
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, OtherComp->GetName());
		if (OtherActor->GetName().Contains(TEXT("Floor"))) {
			// Floor richochets would be too ridic... maybe
			Destroy();
		}
	}
}



