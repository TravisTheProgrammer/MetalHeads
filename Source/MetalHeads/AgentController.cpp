// Fill out your copyright notice in the Description page of Project Settings.

#include "MetalHeads.h"
#include "AgentController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/PawnSensingComponent.h"

AAgentController::AAgentController()
{
	blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	/* Our sensing component to detect players by visibility and noise checks. */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(120.0f);
	PawnSensingComp->SightRadius = 2000;

}

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	/* This is the earliest moment we can bind our delegates to the component _safely_ */
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAgentController::OnSeePawn);
	}


}

void AAgentController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FindClosestEnemy();


}

void AAgentController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	UBehaviorTree *behaviourTreeObject = AMetalHeadsGameMode::LoadObjFromPath<UBehaviorTree>("BlackboardData'/Game/AI/BB_BaseAgent.BB_BaseAgent'");

	UBlackboardData *blackboardData = AMetalHeadsGameMode::LoadObjFromPath<UBlackboardData>("BehaviorTree'/Game/AI/BT_BaseAgent.BT_BaseAgent'");

	blackboardComponent->InitializeBlackboard(*blackboardData);
	behaviorTreeComponent->StartTree(*behaviourTreeObject);

}

void AAgentController::FindClosestEnemy()
{
	ABaseAgent* myself = Cast<ABaseAgent>(GetPawn());

	if (!myself)
	{
		return;
	}

	const FVector MyLoc = myself->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ABaseAgent* BestEnemy = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		ABaseAgent* testAgent = Cast<ABaseAgent>(*It);
		// Is not null, and is an enemy.
		if (testAgent && testAgent->currentTeam != myself->currentTeam)
		{
			const float DistSq = (testAgent->GetActorLocation() - MyLoc).SizeSquared();

			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestEnemy = testAgent;
			}
		}
	}

	if (BestEnemy && blackboardComponent)
	{

		FVector CurrentLocation = blackboardComponent->GetValueAsVector("MoveTarget");
		if (CurrentLocation != BestEnemy->GetActorLocation()) {
			StopMovement();
			 int MoveTargetKey = blackboardComponent->GetKeyID("MoveTarget");
			blackboardComponent->SetValueAsVector(MoveTargetKey, BestEnemy->GetActorLocation());
		}

	}

}

void AAgentController::OnSeePawn(APawn* Pawn)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Found Enemy");


	int DesiredLocationKey = blackboardComponent->GetKeyID("DesiredLocation");
	blackboardComponent->SetValueAsVector(DesiredLocationKey, Pawn->GetActorLocation());*/
}

