// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankComponentAiming.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	NoAmmo
};

class UTankTurret;
class UTankBarrelMeshComp;
class ATank_Projectile;
//eats shit and dies (and also holds barrel's properties and Elevate method, apparently)
UCLASS( ClassGroup=(Tank_Pawn), meta=(BlueprintSpawnableComponent) )
class TANK_PROJECT_API UTankComponentAiming : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankComponentAiming();
	void SetBarrelReference(UTankBarrelMeshComp* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DebugLineOption = false;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;
	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrelMeshComp* barrelComp, UTankTurret* turretComp);
	UFUNCTION(BlueprintCallable)
	int getCurrentAmmo() const;

	///////new stuff \/
	UFUNCTION(BlueprintCallable, Category = "TANK_ACTIONS")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "TANK_SETUP")
		//	UClass* ProjectileBlueprint;
		TSubclassOf<ATank_Projectile> Tank_Projectile_VersionReference;
	ATank_Projectile* projectileClass;

	UPROPERTY(EditAnywhere, Category = "FIRING")
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = "FIRING")
		float ReloadTimeInSeconds = 3;
	UPROPERTY(EditAnywhere, Category = "FIRING")
		int32 MaxAmmo = 69;
	int32 CurrentAmmo = MaxAmmo;

	UTankBarrelMeshComp* TankBarrel = nullptr;
	EFiringStatus GetFiringState() const;
	double LastFireTime = 0;
	///////
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	

	void AimAt(FVector AimLocation);
	FVector GlobalAimDirection;
	void  MoveBarrelTowards(FVector AimDirection);
	void  MoveTurretTowards(FVector AimDirection);
	UTankBarrelMeshComp* GetTankBarrel();
private:
	bool IsBarrelMoving();
	UTankTurret* TankTurret = nullptr;
	//called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
