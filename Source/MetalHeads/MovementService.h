// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "MovementService.generated.h"

/**
 * 
 */
UCLASS()
class METALHEADS_API UMovementService : public UBTService
{
	GENERATED_UCLASS_BODY()
	

		UBlackboardComponent *blackboardComponent;

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
