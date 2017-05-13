// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Forward declarations
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
class UTankComponentAiming;
class UTankBarrelMeshComp;
UCLASS()
class TANK_PROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelMeshComp* BarrelToSet);

protected:
	UTankComponentAiming* TankAimingComponent = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 1000;

	
	
};

