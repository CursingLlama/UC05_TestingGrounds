// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FocusAtActor.generated.h"

/**
 * 
 */
UCLASS()
class UC05_TESTINGGROUNDS_API UFocusAtActor : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, category = "Blackboard") FBlackboardKeySelector FocusPointKey;
};
