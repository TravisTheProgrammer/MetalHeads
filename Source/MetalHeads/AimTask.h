// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "AimTask.generated.h"

/**
 * 
 */
UCLASS()
class METALHEADS_API UAimTask : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

		UBlackboardComponent *blackboardComponent;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
