// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tank_Projectile.generated.h"

UCLASS()
class TANK_PROJECT_API ATank_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATank_Projectile();
	//UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* MovementComponent;
	void LaunchProjectile(float speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
