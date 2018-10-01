// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class UC05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Setup") void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 0, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool FindEmptySpace(FVector &OutLocation, float Radius);

	bool CanSpawnAtLocation(FVector Location, float Radius);
	
};