// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "BaseAgent.h"

#include "Bullet.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "Runtime/Engine/Classes/Components/SplineMeshComponent.h"


// Sets default values
ABaseAgent::ABaseAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add default components to all properties in the editor
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	mainFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AnimComponent"));
	myGun = CreateDefaultSubobject<UGun>(TEXT("MyGun"));
	statusText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StatusText"));
	//woundText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WoundText"));
	aimSpline = CreateDefaultSubobject<USplineComponent>(TEXT("AimSpline"));
	aimMesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("AimMesh"));

	statusText->SetText(TEXT("---"));
	//woundText->SetText(TEXT("No wounds"));

	headBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadHitbox"));
	torsoBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TorsoHitbox"));
	leftArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmHitbox"));
	rightArmBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHitbox"));
	leftLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLegHitbox"));
	rightLegBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegHitbox"));

	headAimLoc = CreateDefaultSubobject<USceneComponent>(TEXT("HeadAimLocation"));
	bodyAimLoc = CreateDefaultSubobject<USceneComponent>(TEXT("BodyAimLocation"));
	legsAimLoc = CreateDefaultSubobject<USceneComponent>(TEXT("LegsAimLocation"));

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

	headBox->AttachTo(GetCapsuleComponent());
	torsoBox->AttachTo(GetCapsuleComponent());
	leftArmBox->AttachTo(GetCapsuleComponent());
	rightArmBox->AttachTo(GetCapsuleComponent());
	leftLegBox->AttachTo(GetCapsuleComponent());
	rightLegBox->AttachTo(GetCapsuleComponent());

	headAimLoc->AttachTo(GetCapsuleComponent());
	bodyAimLoc->AttachTo(GetCapsuleComponent());
	legsAimLoc->AttachTo(GetCapsuleComponent());

	mainFlipbook->AttachTo(GetCapsuleComponent());
	statusText->AttachTo(GetCapsuleComponent());
	//woundText->AttachTo(GetCapsuleComponent());
	aimSpline->AttachTo(GetCapsuleComponent());
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

	// Set our default states
	currentAction = EActionState::Idle;
	movementStruct.currentDesination = this->GetActorLocation();

	// start checking possible bleedout every second.
	GetWorldTimerManager().SetTimer(BleedTickPerSecondHandler, this, &ABaseAgent::CheckBleed, 1.0f, true);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, FString::FromInt(RootComponent->IsSimulatingPhysics()));
	aimSpline->SetLocationAtSplinePoint(0, mainFlipbook->GetSocketLocation(TEXT("GunBarrel")), ESplineCoordinateSpace::World);

	aimMesh->SetStartScale(FVector2D(0.1f, 0.1f));
	aimMesh->SetEndScale(FVector2D(0.1f, 0.1f));
	aimMesh->SetStartTangent(FVector(1, 0, 0));
	aimMesh->SetEndTangent(FVector(1, 0, 0));
	// Static spline mesh should be set in blueprint implimentation.
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
		//FRotator rot = FRotator(45.0f, 90.0f, 0);
		FRotator rot = mainCam->GetComponentRotation();
		rot.Pitch += 90;
		rot.Yaw += 180;
		FVector pos = FVector(0, 0, 200.0f);
		statusText->SetRelativeLocation(pos);
		statusText->SetWorldRotation(rot);

		// bootiful conversions
		statusText->SetText(FText::FromString(AMetalHeadsGameMode::GetEnumValueToString("EGunState", (int32) myGun->currentGunState)));
		//FRotator otherRot = mainFlipbook->GetComponentRotation();
		
		//statusText->SetText(FText::FromString(otherRot.ToString()));

		// Update the aim render line
		aimMesh->SetStartPosition(mainFlipbook->GetSocketLocation(TEXT("GunBarrel")));
		//aimMesh->SetEndPosition(mainFlipbook->GetSocketLocation(TEXT("GunBarrel")) + AMetalHeadsGameMode::RIGHT() * 500);
		aimMesh->SplineUpDir = mainCam->GetComponentLocation();

		// Determine where the line should draw (if at all!)
		if (currentAction == EActionState::Aiming && currentTarget) {
			aimMesh->SetHiddenInGame(false);
			if (currentAimLocation == EAimLocation::Head) {
				aimMesh->SetEndPosition(currentTarget->headAimLoc->GetComponentLocation());
			}
			else if (currentAimLocation == EAimLocation::Body) {
				aimMesh->SetEndPosition(currentTarget->bodyAimLoc->GetComponentLocation());
			}
			else if (currentAimLocation == EAimLocation::Legs) {
				aimMesh->SetEndPosition(currentTarget->legsAimLoc->GetComponentLocation());
			}else{
				aimMesh->SetEndPosition(currentTarget->GetActorLocation() + FVector(0, 0, 90.0f));
			}
		}else{
			aimMesh->SetHiddenInGame(true);
		}
	}

	//if (FMath::RandRange(1, 20) == 20) {
	//Shoot();
	//}
}

// Called to bind functionality to input
void ABaseAgent::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// If I needed direct shortcuts etc, I'd put them here
}

void ABaseAgent::Aim(ABaseAgent* target)
{
	if (currentAction != EActionState::Aiming){
		currentTarget = target;
		currentAction = EActionState::Aiming;

		currentAimTime = 0;

		if (targetAimTime > 0.1) {
			this->GetWorld()->GetTimerManager().SetTimer(AimingHandler, this, &ABaseAgent::AimTick, GetWorld()->DeltaTimeSeconds, true);
		}
		else {
			// SHOOT ALL DAY ERRY DAY
			Shoot();
		}

	}

	
	//aimSpline->SetLocationAtSplinePoint(1, target->GetActorLocation(), ESplineCoordinateSpace::World);

}

void ABaseAgent::AimTick()
{
	currentAimTime += GetWorld()->DeltaTimeSeconds;
	if (currentAimTime >= targetAimTime) {
		Shoot();
		StopAimTick();
	}
}

void ABaseAgent::StopAimTick()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(AimingHandler)) {
		GetWorld()->GetTimerManager().ClearTimer(AimingHandler);
		currentAimTime = 0;
		currentAction = EActionState::Idle;
		// other reset logic would go here.
	}
}

void ABaseAgent::Shoot()
{
	// Ladies and gentlemen, the most seemlying useless state change.
	currentAction = EActionState::Shooting;
	if (myGun) {
		this->myGun->ShootGun(currentAimTime, currentTarget);
	}
	currentAimTime = 0;
	// Ensure we're ready to take more actions
	currentAction = EActionState::Idle;
}

void ABaseAgent::TakeWound(float woundChance, EHitLocation location) {
	float result = FMath::RandRange(1, 100);
	if (result <= woundChance) {
		if (location == EHitLocation::Head) {
			// congrats, you died.
			Die(ECauseOfDeath::Headshot);
		}
		else {
			statusStruct.AddStatus(location);
		}
		//FString locationStr = AMetalHeadsGameMode::GetEnumValueToString<EHitLocation>("EHitLocation", location);
		//FString message = this->GetName() + " has been wounded in their " + locationStr + "!";
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, message);
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("Bullet deflected!"));
		
		// NOTE: there's not much that's needed here. Physics makes the bullets bounce by default!
		// Perhaps a cool particle?
	}

	
}

void ABaseAgent::Die(ECauseOfDeath cod)
{
	// death logic.

	// TODO: switch flipbook and play death animation.
	deathStatus = cod; // Anything but "None" simply means they're dead, but a death status is
	// passed for messages etc.

	// TODO: have timer tick for length of death, then destroy this.
	this->GetWorld()->GetTimerManager().SetTimer(DeathCountdownHandler, this, &ABaseAgent::JustDie, deathDelay, false);
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

void ABaseAgent::CheckBleed() 
{
	// Get our status struct to handle bleedout (if applicable).
	if (statusStruct.BleedTick()) {
		Die(ECauseOfDeath::Hypooleum);
	}
}


