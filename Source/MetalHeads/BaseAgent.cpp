// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "BaseAgent.h"


// Sets default values
ABaseAgent::ABaseAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add default components to all properties in the editor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mainFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AnimComponent"));
	myGun = CreateDefaultSubobject<UGun>(TEXT("MyGun"));
	//navsys = CreateDefaultSubobject<UNavigationSystem>(TEXT("NavSystem"));
	//agentAI = CreateDefaultSubobject<AAgentController>(TEXT("AgentController"));

	headBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadHitbox"));
	torsoBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TorsoHitbox"));
	leftArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmHitbox"));
	rightArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHitbox"));
	leftLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLegHitbox"));
	rightLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegHitbox"));

	// Attach components to root
	headBox->AttachTo(RootComponent);
	mainFlipbook->AttachTo(RootComponent);

	// Final tweaks before construction is done
	UPaperFlipbook* testFlip = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Art/Sprites/MH_Testaim_Flipbook.MH_Testaim_Flipbook'")));
	mainFlipbook->SetRelativeLocation(FVector(0, 0, 80));
	mainFlipbook->SetFlipbook(testFlip);

}

// Called when the game starts or when spawned
void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();

	// Bind hitbox colliders
	headBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	torsoBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	leftArmBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	rightArmBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	leftLegBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	rightLegBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	
}

// Called every frame
void ABaseAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	UCameraComponent* mainCam = AMetalHeadsGameMode::GetMainCamera();

	// double check the pointer
	if (mainCam)
	{
		AMetalHeadsGameMode::RotateFlipbookOrtho(mainFlipbook, mainCam->ComponentToWorld.Rotator());
	}
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

// Collision Event
void ABaseAgent::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


