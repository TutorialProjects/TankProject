// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATankPawn;
UCLASS()
class TANK_PROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATankPawn* GetControlledTankPawn() const;
	ATankPawn* GetPlayerTank() const;
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	
	
};
