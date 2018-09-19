// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Public/PatrolRoute.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Aborted; }
	
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Patrol Route has no points."), *ControlledPawn->GetName());
		return EBTNodeResult::Aborted;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	int32 Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	++Index %= PatrolPoints.Num();
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, Index);
		
	return EBTNodeResult::Succeeded;
}

