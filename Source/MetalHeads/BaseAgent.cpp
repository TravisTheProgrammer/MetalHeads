// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "BaseAgent.h"

#include "Bullet.h"


// Sets default values
ABaseAgent::ABaseAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add default components to all properties in the editor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mainFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AnimComponent"));
	myGun = CreateDefaultSubobject<UGun>(TEXT("MyGun"));
	statusText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StatusText"));
	woundText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WoundText"));

	statusText->SetText(TEXT("---"));
	woundText->SetText(TEXT("No wounds"));

	headBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadHitbox"));
	torsoBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TorsoHitbox"));
	leftArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmHitbox"));
	rightArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHitbox"));
	leftLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLegHitbox"));
	rightLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegHitbox"));

	// Turn on collider physics
	//headBox->SetNotifyRigidBodyCollision(true);
	headBox->BodyInstance.SetCollisionProfileName("BodyPart");
	torsoBox->BodyInstance.SetCollisionProfileName("BodyPart");
	leftArmBox->BodyInstance.SetCollisionProfileName("BodyPart");
	rightArmBox->BodyInstance.SetCollisionProfileName("BodyPart");
	leftLegBox->BodyInstance.SetCollisionProfileName("BodyPart");
	rightArmBox->BodyInstance.SetCollisionProfileName("BodyPart");
	
	headBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	torsoBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	leftArmBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	rightArmBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	leftLegBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	rightLegBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Bind hitbox colliders
	headBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	torsoBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	leftArmBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	rightArmBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	leftLegBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);
	rightLegBox->OnComponentHit.AddDynamic(this, &ABaseAgent::OnHit);

	// Attach components to root

	// Also tag hitboxes to appropriate enum values (ensure each string is a enum value)
	headBox->ComponentTags.Add("Head");
	torsoBox->ComponentTags.Add("LeftArm");
	leftArmBox->ComponentTags.Add("RightArm");
	rightArmBox->ComponentTags.Add("Torso");
	leftLegBox->ComponentTags.Add("LeftLeg");
	rightLegBox->ComponentTags.Add("RightLeg");

	headBox->AttachTo(RootComponent);
	torsoBox->AttachTo(RootComponent);
	leftArmBox->AttachTo(RootComponent);
	rightArmBox->AttachTo(RootComponent);
	leftLegBox->AttachTo(RootComponent);
	rightLegBox->AttachTo(RootComponent);

	mainFlipbook->AttachTo(RootComponent);
	statusText->AttachTo(RootComponent);
	woundText->AttachTo(RootComponent);
	//statusText->SetRelativeLocation(FVector(0, 0, 200.0f));

	// Final tweaks before construction is done
	UPaperFlipbook* testFlip = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), NULL, TEXT("PaperFlipbook'/Game/Art/Sprites/MH_Testaim_Flipbook.MH_Testaim_Flipbook'")));
	mainFlipbook->SetRelativeLocation(FVector(0, 0, 80));
	mainFlipbook->SetFlipbook(testFlip);

}

// Called when the game starts or when spawned
void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();



	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, FString::FromInt(RootComponent->IsSimulatingPhysics()));

}

// Called every frame
void ABaseAgent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	UCameraComponent* mainCam = AMetalHeadsGameMode::GetMainCamera();

	// double check the pointer
	if (mainCam)
	{
		AMetalHeadsGameMode::RotateOrtho(mainFlipbook, mainCam->ComponentToWorld.Rotator());
		// Precook prototype text
		FRotator rot = FRotator(45.0f, 90.0f, 0);
		FVector pos = FVector(0, 0, 200.0f);
		statusText->SetRelativeLocationAndRotation(pos, rot);

		// bootiful conversions
		statusText->SetText(FText::FromString(AMetalHeadsGameMode::GetEnumValueToString("EGunState", (int32) myGun->currentGunState)));
		//FRotator otherRot = mainFlipbook->GetComponentRotation();
		
		//statusText->SetText(FText::FromString(otherRot.ToString()));
	}

	//if (FMath::RandRange(1, 20) == 20) {
		if (myGun) {
			this->myGun->ShootGun(FMath::FRandRange(0, 45.0f));
		}
	//}
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

// Step one: simply register hits on hitboxes
void ABaseAgent::TakeWound(float woundChance, EHitLocation location) {
	float result = FMath::RandRange(1, 100);
	if (result <= woundChance) {
		FString locationStr = AMetalHeadsGameMode::GetEnumValueToString<EHitLocation>("EHitLocation", location);
		FString message = this->GetName() + " has been wounded in their " + locationStr + "!";
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, message);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("Bullet deflected!"));
	}

	
}

// Collision Event
void ABaseAgent::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	ABullet* potentialBullet = Cast<ABullet>(OtherActor);
	if (potentialBullet) {
		float woundChance = potentialBullet->woundChance;
		FString tagName = "";
		TArray<FName> tags = OtherComp->ComponentTags;
		for (const auto& tag : tags) {
			// simply nab the first enum tag we hit
			tagName = tag.ToString();
			EHitLocation potentialEnum = AMetalHeadsGameMode::GetEnumValueFromString<EHitLocation>("EHitLocation", tagName);
			if (potentialEnum != EHitLocation::None) {
				TakeWound(woundChance, potentialEnum);
			}
		}
		//EHitLocation location = AMetalHeadsGameMode::GetEnumValueFromString("EHitLocation", )
	}
}


