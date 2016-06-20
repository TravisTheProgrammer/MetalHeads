// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "AgentController.h"
#include "BaseAgent.h"
#include "MoveTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UMoveTask::UMoveTask(const FObjectInitializer &initializer) : Super(initializer)
{

	NodeName = "MoveTask";


}

EBTNodeResult::Type UMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAgentController* AIController = Cast<AAgentController>(OwnerComp.GetOwner());

	if (AIController) {

		ABaseAgent* myPawn = Cast<ABaseAgent>(AIController->GetPawn());

		if (myPawn) {

			blackboardComponent = Cast<UBlackboardComponent>(AIController->GetComponentByClass(UBlackboardComponent::StaticClass()));
			int moveTargetID = blackboardComponent->GetKeyID("MoveTarget");
			FVector currentTarget = blackboardComponent->GetValue<UBlackboardKeyType_Vector>(moveTargetID);

			if (currentTarget != myPawn->movementStruct.currentDesination) {
				blackboardComponent->SetValue<UBlackboardKeyType_Vector>(moveTargetID, myPawn->movementStruct.currentDesination);
			}
		}
	}
	else
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}

FString UMoveTask::GetStaticDescription() const {
	return TEXT("Move to new destination, if updated");
}


