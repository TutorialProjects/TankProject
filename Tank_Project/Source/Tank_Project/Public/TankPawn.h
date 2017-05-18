// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Forward declarations
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
//class UTankComponentAiming;
class UTankBarrelMeshComp;
class UTankTurret;
class ATank_Projectile;
class UTankMovementComponent;
UCLASS()
class TANK_PROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	UPROPERTY(EditAnywhere, Category = "FIRING")
		float LaunchSpeed = 1000.f;

	UFUNCTION(BlueprintCallable, Category = "TANK_ACTIONS")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "TANK_SETUP")
		//	UClass* ProjectileBlueprint;
		TSubclassOf<ATank_Projectile> Tank_Projectile_VersionReference;
	UTankBarrelMeshComp* TankBarrel;
	//TSubclassOf<UProjectileMovementComponent> BallMonkeys2; 
	//AActor shit;
	//TSubclassOf<AActor> cocks; //https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
protected:
//	UPROPERTY(BlueprintReadOnly)
//	UTankComponentAiming* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	

	UPROPERTY(EditDefaultsOnly,Category = "FIRING")
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	
	
};

