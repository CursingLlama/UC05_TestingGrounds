// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};

USTRUCT(BlueprintType)
struct FMinMax
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinMax Struct") float Minimum = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinMax Struct") float Maximum = 1;
};

class UActorPool;

UCLASS()
class UC05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()


public:	
	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawning") void PlaceActors(TSubclassOf<AActor> ToSpawn, FMinMax Spawn, FMinMax Scale, float Radius = 300);
	UFUNCTION(BlueprintCallable, Category = "Spawning") void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FMinMax Spawn, float Radius = 200);
	
	UFUNCTION(BlueprintCallable, Category = "Pool") void SetPool(UActorPool* Pool);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning") FBox SpawningExtents;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation") FVector NavMeshOffset;

private:

	void PositionNavMeshBoundsVolume();
	
	bool FindEmptySpace(FVector &OutLocation, float Radius);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, const int32 &MinSpawn, const int32 &MaxSpawn, float MinScale, float MaxScale, float Radius);

	template <class T>
	void PlaceActor(TSubclassOf<T> ToSpawn, const FSpawnPosition& SpawnPosition);

	UActorPool* PoolRef;

	AActor* NavMeshBoundsVolume;
};
