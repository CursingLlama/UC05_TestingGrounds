// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	if (!ToSpawn) { return; }
	
	int32 NumSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumSpawn; i++)
	{
		FVector SpawnPoint;
		float RandScale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptySpace(SpawnPoint, Radius * RandScale))
		{
			FRotator Rotation = FRotator(0.0f, FMath::RandRange(-180.0f, 180.0f), 0.0f);
			AActor* Actor = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, Rotation);
			Actor->SetActorScale3D(FVector(RandScale));
			Actor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}	
}

void ATile::SetPool(UActorPool * Pool)
{
	PoolRef = Pool;
	UE_LOG(LogTemp, Warning, TEXT("Pool Ref set on [%s]"), *GetName())
}

bool ATile::FindEmptySpace(FVector& OutLocation, float Radius)
{
	FBox RandBox = FBox(FVector(0.0f, -1900.0f, 0.0f), FVector(3900.0f, 1900.0f, 0.0f));
	FVector EmptySpace = FMath::RandPointInBox(RandBox);
	const int32 MaxTries = 50;
	for (size_t i = 0; i < MaxTries; i++)
	{
		if (CanSpawnAtLocation(EmptySpace, Radius))
		{
			OutLocation = EmptySpace;
			return true;
		}
		else
		{
			EmptySpace = FMath::RandPointInBox(RandBox);
		}
	}
	
	return false;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	FHitResult HitResult;
	bool bHasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	
	///DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 24, (bHasHit ? FColor::Red : FColor::Green), true, 100.0f);
	
	return !bHasHit;
}

