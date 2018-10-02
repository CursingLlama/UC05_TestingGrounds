// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class UC05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

	class UActorPool;

public:	
	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup") void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 0, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Pool") void SetPool(UActorPool* Pool);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	bool FindEmptySpace(FVector &OutLocation, float Radius);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* PoolRef;
};
