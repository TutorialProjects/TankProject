// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Forward declarations
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
UCLASS()
class TANK_PROJECT_API ATankPawn : public APawn
{
	GENERATED_BODY()
		
public:
	FTankDelegate OnTankDeath;
	// Sets default values for this pawn's properties
	ATankPawn();
	UPROPERTY(EditAnywhere,Category = "SETUP")
	float TotalHealth =100;
	UPROPERTY(VisibleAnywhere, Category = "HEALTH")
	float CurrentHealth;
	float DamageToApply;
	UFUNCTION(BlueprintPure, Category = "HEALTH")
	float GetHealthPercent();
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser);
	
	//TSubclassOf<UProjectileMovementComponent> BallMonkeys2; 
	//AActor shit;
	//TSubclassOf<AActor> cocks; //https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
protected:



private:	
	// Called every frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	
	
};

