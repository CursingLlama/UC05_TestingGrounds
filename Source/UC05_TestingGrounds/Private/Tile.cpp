// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawningExtents = FBox(FVector(0.0f, -1900.0f, 0.0f), FVector(3900.0f, 1900.0f, 0.0f));
	NavMeshOffset = FVector(2000.0f, 0.0f, 0.0f);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FMinMax Spawn, FMinMax Scale, float Radius)
{
	if (!ToSpawn) { return; }
	
	RandomlyPlaceActors<AActor>(ToSpawn, Spawn.Minimum, Spawn.Maximum, Scale.Minimum, Scale.Maximum, Radius);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FMinMax Spawn, float Radius)
{
	if (!ToSpawn) { return; }

	RandomlyPlaceActors<APawn>(ToSpawn, Spawn.Minimum, Spawn.Maximum, 1, 1, Radius);
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, const int32 &MinSpawn, const int32 &MaxSpawn, float MinScale, float MaxScale, float Radius)
{
	int32 NumSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptySpace(SpawnPosition.Location, Radius * SpawnPosition.Scale))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor<T>(ToSpawn, SpawnPosition);
		}
	}
}

template <class T>
void ATile::PlaceActor(TSubclassOf<T> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	T* Actor = GetWorld()->SpawnActor<T>(ToSpawn, SpawnPosition.Location, FRotator(0, SpawnPosition.Rotation, 0));
	if (Actor)
	{
		Actor->SetActorScale3D(FVector(SpawnPosition.Scale));
		Actor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}
template <>
void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location, FRotator(0, SpawnPosition.Rotation, 0));
	if (Pawn)
	{
		Pawn->SetActorScale3D(FVector(SpawnPosition.Scale));
		Pawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		Pawn->SpawnDefaultController();
		Pawn->Tags.Add(FName("Guard"));
	}
}


void ATile::SetPool(UActorPool * InPool)
{
	PoolRef = InPool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = PoolRef->Checkout(); //No need to check pointer as this is only called when setting PoolRef
	if (!NavMeshBoundsVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] NavMeshBoundsVolume not properly checked out!"), *GetName());
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavMeshOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

bool ATile::FindEmptySpace(FVector& OutLocation, float Radius)
{
	
	FVector EmptySpace = FMath::RandPointInBox(SpawningExtents);
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
			EmptySpace = FMath::RandPointInBox(SpawningExtents);
		}
	}
	
	return false;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PoolRef && NavMeshBoundsVolume)
	{
		PoolRef->Return(NavMeshBoundsVolume);
	}
	Super::EndPlay(EndPlayReason);
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

