// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class UC05_TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

private:

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)	class USkeletalMeshComponent* Mesh1P;

	class AGun* Gun;

public:
	// Sets default values for this character's properties
	AMannequin();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) float BaseLookUpRate;

	/** Gun blueprint to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AGun> GunBlueprint;

	/** AnimMontage to play each time we fire in first person*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) class UAnimMontage* FirstPersonFireMontage;

	/** AnimMontage to play each time we fire in third person*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) class UAnimMontage* ThirdPersonFireMontage;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon") void PullTrigger();
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void UnPossessed() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};
