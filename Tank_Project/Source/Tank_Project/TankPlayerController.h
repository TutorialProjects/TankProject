// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class TANK_PROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
		void Tick(float DeltaTime);
public:

	virtual void BeginPlay() override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& outLookDirection) const;
	bool GetLookVectorHitLocation(FVector Direction, FVector &outHitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "SETUP")
	void FoundAimingComponent(UTankComponentAiming* AimingCompRef); //sets the output of the blueprint implementable event
};
