// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class UC05_TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()
	
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)	class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGun();

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = Gun) void OnFire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetSkeletalMeshComponent();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	class UAnimMontage* FireAnimation;

	/** AnimInstance to play the fire animation on */
	class UAnimInstance* AnimInstance;

	/** Number of rounds per minute the gun is capable of firing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) float RoundsPerMinute = 600;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
private:	
	
	float LastFired = -1000;
	float FireRate;
};
