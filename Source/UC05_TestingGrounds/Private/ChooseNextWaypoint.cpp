// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Public/PatrollingGuard.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	APatrollingGuard* ControlledPawn = Cast<APatrollingGuard>(AIController->GetPawn());
	TArray<AActor*> PatrolPoints = ControlledPawn->GetPatrolPoints();
	
	int32 Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	++Index %= PatrolPoints.Num();
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, Index);
		
	return EBTNodeResult::Succeeded;
}

