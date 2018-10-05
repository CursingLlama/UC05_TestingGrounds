// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Has nothing to checkout!"), *GetName());
		return nullptr;
	}
	else
	{
		AActor* Actor = Pool.Pop();
		///UE_LOG(LogTemp, Warning, TEXT("[%s] Checking out %s"), *GetName(), *Actor->GetName());
		return Actor;
	}

	
	
}

void UActorPool::Return(AActor * ActorToReturn)
{
	if (!ActorToReturn)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] attempted to return nullptr!"), *GetName())
		return;
	}
	else
	{
		///UE_LOG(LogTemp, Warning, TEXT("[%s] returned to pool!"), *ActorToReturn->GetName());
		Pool.Emplace(ActorToReturn);
	}
	
}

void UActorPool::Add(AActor * ActorToAdd)
{
	Return(ActorToAdd);
}
