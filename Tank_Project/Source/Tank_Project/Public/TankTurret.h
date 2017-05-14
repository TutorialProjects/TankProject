// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank_Pawn), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Variable", "Sockets", "Lighting", "Rendering", "Tags", "Component_Replication", "Cooking", "Mobile", "Physics", "Events"))
class TANK_PROJECT_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Turn(float relativeSpeed);

	UPROPERTY(EditAnywhere, Category = TURRET_PROPERTIES)
		float MaxDegreesPerSecond = 75;


};