// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class METALHEADS_API AAgentController : public AAIController
{
	GENERATED_BODY()
	
public:

	AAgentController();

	virtual void Possess(class APawn* InPawn) override;

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/* Properties */

	UPROPERTY(EditAnywhere)
		class UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(EditAnywhere)
		UBehaviorTreeComponent* behaviorTreeComponent;

	UPROPERTY(EditAnywhere)
		UBlackboardComponent* blackboardComponent;

	/* Functions */

	UFUNCTION()
	void OnSeeAgent(APawn* enemyAgent);

	void FindClosestEnemy();
	
	void Test();
};
