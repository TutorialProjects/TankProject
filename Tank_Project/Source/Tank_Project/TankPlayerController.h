// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/TankPawn.h"
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
	ATankPawn* GetControlledTank() const;
	virtual void BeginPlay() override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& outLookDirection) const;
	bool GetLookVectorHitLocation(FVector Direction, FVector &outHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 500000.f;
	
};
