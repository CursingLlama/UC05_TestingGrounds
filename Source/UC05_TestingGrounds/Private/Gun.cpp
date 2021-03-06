// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "BallProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P and FP_Gun
	// are set in the derived blueprint asset named Gun_BP to avoid direct content references in C++.

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	///FP_Gun->SetupAttachment(RootComponent);
	SetRootComponent(FP_Gun);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	FireRate = 60.0f / RoundsPerMinute;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USkeletalMeshComponent * AGun::GetSkeletalMeshComponent()
{
	return FP_Gun;
}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{	
			float Time = GetWorld()->GetTimeSeconds();
			if (Time < LastFired + FireRate) ///Trying to fire too soon?
			{ 
				return; 
			}
			LastFired = Time;

			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();
			
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			
			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{		
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

