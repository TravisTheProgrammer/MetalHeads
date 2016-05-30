// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "BaseAgent.h"


// Sets default values
ABaseAgent::ABaseAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mainFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AnimComponent"));

	mainFlipbook->AttachTo(RootComponent);
	UPaperFlipbook* testFlip = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Art/Sprites/TestBook.TestBook'")));
	mainFlipbook->SetFlipbook(testFlip);
	RotateFlipbookTowardsCamera();
}

// Called when the game starts or when spawned
void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	ABaseAgent::RotateFlipbookTowardsCamera();
}

// Called to bind functionality to input
void ABaseAgent::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABaseAgent::Aim(ABaseAgent* target)
{
}

void ABaseAgent::Shoot()
{
}


void ABaseAgent::RotateFlipbookTowardsCamera()
{
	if (!mainCam) {
		// if we haven't set our main camera pointer yet, go get it
		mainCam = AMetalHeadsGameMode::GetMainCamera();
	}
	if (!mainCam)
	{
		// double check the pointer
#if UE_BUILD_DEBUG
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ERROR: No Main Camera Found!");
#endif
		return;
	}
	
	//FVector directionVector =  mainFlipbook->ComponentToWorld.GetLocation() - mainCam->ComponentToWorld.GetLocation();
	//directionVector.Normalize();
	// "look at"
	//FRotator flipbookRot = FRotationMatrix::MakeFromZ(directionVector).Rotator();
	//flipbookRot.Yaw = 90;

	// invert our direction
	//directionVector = -directionVector;

	//
	//FRotator flipbookRot = FRotator::ZeroRotator;
	//flipbookRot.Pitch = 135;
	//flipbookRot.Roll = -45;
	//flipbookRot.Yaw = 0;

	// See what the camera's rotation is
	FRotator camRot = mainCam->ComponentToWorld.Rotator();

	// Adjust for our own rotator
	FRotator flipbookRot = FRotator();
	flipbookRot.Roll = camRot.Pitch;
	flipbookRot.Yaw = camRot.Yaw + 90;
	
	mainFlipbook->SetWorldRotation(flipbookRot);
}

