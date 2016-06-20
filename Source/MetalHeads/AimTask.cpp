// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "AimTask.h"
#include "AgentController.h"
#include "BaseAgent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UAimTask::UAimTask(const FObjectInitializer &initializer) : Super(initializer)
{

	NodeName = "AimTask";

}

EBTNodeResult::Type UAimTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAgentController* AIController = Cast<AAgentController>(OwnerComp.GetOwner());

	if (AIController) {

		ABaseAgent* myPawn = Cast<ABaseAgent>(AIController->GetPawn());

		if (myPawn) {

			blackboardComponent = Cast<UBlackboardComponent>(AIController->GetComponentByClass(UBlackboardComponent::StaticClass()));
			int enemyID = blackboardComponent->GetKeyID("EnemyAgent");
			ABaseAgent* enemyTarget = Cast<ABaseAgent>(blackboardComponent->GetValue<UBlackboardKeyType_Object>(enemyID));

			if (enemyTarget) {
				myPawn->Aim(enemyTarget);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

FString UAimTask::GetStaticDescription() const {
	return TEXT("Initiate aiming at a target, if there's on the BB");
}



