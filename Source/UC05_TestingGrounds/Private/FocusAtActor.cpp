// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtActor.h"
#include "AIController.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UFocusAtActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AActor* Focus = Cast<AActor>(Blackboard->GetValueAsObject(FocusPointKey.SelectedKeyName));
	if(Focus)
	{
		Controller->SetFocus(Focus);
	}
	
	return EBTNodeResult::Succeeded;
}
