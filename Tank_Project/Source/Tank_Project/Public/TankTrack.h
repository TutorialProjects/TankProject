// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is for licking balls and also for setting track speeds derperdirp
 */
UCLASS(ClassGroup = (Tank_Pawn), meta = (BlueprintSpawnableComponent))
class TANK_PROJECT_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "INPUT")
	void SetThrottle(float Throttle);
	// max force per track, in newtons (penis)
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce=400000;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

	void ApplyAntiForce();


	UTankTrack();
	void BeginPlay();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
	
	void DriveTrack();

};
