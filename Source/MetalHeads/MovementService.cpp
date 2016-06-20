// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "AgentController.h"
#include "BaseAgent.h"
#include "MovementService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UMovementService::UMovementService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "MovementService";

	Interval = 0.5f;
	//RandomDeviation = 0.1f;
}

void UMovementService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("UMyBTService TickNode"));

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



}


