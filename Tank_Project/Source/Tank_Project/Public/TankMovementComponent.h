// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANK_PROJECT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category = "Input")
	void IntendMoveForward(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);
private:
	UTankTrack* LeftTrack;
	 UTankTrack* RightTrack;
	
	
};
