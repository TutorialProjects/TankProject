// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Forward declarations
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
class UTankComponentAiming;
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
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Tank_Setup)
	void SetBarrelReference(UTankBarrelMeshComp* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Tank_Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Tank_Actions)
	void Fire();

	UPROPERTY(EditAnywhere, Category = TANK_SETUP)
		//	UClass* ProjectileBlueprint;
		TSubclassOf<ATank_Projectile> Tank_Projectile_VersionReference;
	UTankBarrelMeshComp* TankBarrel;
	//TSubclassOf<UProjectileMovementComponent> BallMonkeys2; 
	//AActor shit;
	//TSubclassOf<AActor> cocks; //https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
protected:
	UPROPERTY(EditAnywhere)
	UTankComponentAiming* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovingComponent = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = FIRING)
		float LaunchSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly,Category = FIRING)
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	
	
};

