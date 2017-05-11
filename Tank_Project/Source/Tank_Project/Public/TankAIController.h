// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/TankPawn.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_PROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	APawn* GetControlledPawn() const;
	ATankPawn* GetPlayerTank() const;
	virtual void BeginPlay() override;
	
	
	
};
