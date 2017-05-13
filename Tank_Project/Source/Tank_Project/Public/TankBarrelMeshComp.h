// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrelMeshComp.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank_Pawn), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision","Variable","Sockets","Lighting","Rendering","Tags","Component_Replication","Cooking","Mobile","Physics","Events"))
class TANK_PROJECT_API UTankBarrelMeshComp : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
		void Elevate(float relativeSpeed);
	
	UPROPERTY(EditAnywhere, Category = BARREL_PROPERTIES)
		float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = BARREL_PROPERTIES)
		float MaxEvelvation = 30;
	UPROPERTY(EditAnywhere, Category = BARREL_PROPERTIES)
		float MinEvelvation = -10;
	
};
