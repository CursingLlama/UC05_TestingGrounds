// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class UC05_TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
public:
	TArray<AActor*> GetPatrolPoints();

private:
	UPROPERTY(EditInstanceOnly, category = "Patrol Route") TArray<AActor*> PatrolPoints;
	
	
};
