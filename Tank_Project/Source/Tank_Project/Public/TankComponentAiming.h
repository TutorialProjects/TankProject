// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankComponentAiming.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankTurret;
class UTankBarrelMeshComp;
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
		EFiringStatus FiringState = EFiringStatus::Aiming;
	UFUNCTION(BlueprintCallable)
		void Initialize(UTankBarrelMeshComp* barrelComp, UTankTurret* turretComp);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector AimLocation, float LaunchSpeed);
	void  MoveBarrelTowards(FVector AimDirection);
	void  MoveTurretTowards(FVector AimDirection);
	UTankBarrelMeshComp* GetTankBarrel();
private:
	UTankBarrelMeshComp* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;
	
	
};
