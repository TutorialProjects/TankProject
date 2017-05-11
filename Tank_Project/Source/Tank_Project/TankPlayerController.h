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
	
};
