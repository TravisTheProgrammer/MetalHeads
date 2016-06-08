// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MetalHeadsGameMode.h"
#include "PaperFlipbookComponent.h"

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class METALHEADS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/* Functions */

	// Set up the bullet
	void Init(FVector bulletDirection, const float& bulletRadius, const float& lethality, const float& bulletVelocity);

	UFUNCTION()
		void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/* Properties */

	// Nice simple sphere collider to detect our collides
	UPROPERTY(EditAnywhere)
		USphereComponent* bulletCollider;

	// Stored value of what % chance the bullet has to wound a target, set by Init()
	UPROPERTY(EditAnywhere)
		float woundChance;

	// Aw yeah built in bullet physics!
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* bulletMovement;

	// Visual flipbook component for the bullet
	UPROPERTY(EditAnywhere)
		UPaperFlipbookComponent* myFlipbook;

	
};
