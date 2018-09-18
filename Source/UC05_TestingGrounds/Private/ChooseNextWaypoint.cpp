// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BTNode.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Llama: c++ choose next waypoint"))
	return EBTNodeResult::Succeeded;
}

