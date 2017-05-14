// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankBarrelMeshComp.h"




void UTankBarrelMeshComp::Elevate(float speedMultiplier = 1) {
	speedMultiplier = FMath::Clamp(speedMultiplier,-1.f,1.f);
	auto ElevationChange = (MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds)) * speedMultiplier;
	auto RawNewElevation = Super::RelativeRotation.Pitch + ElevationChange;
	RawNewElevation = FMath::Clamp(RawNewElevation, CurrentMinEvelvationClamp, MaxEvelvationClamp);
	Super::SetRelativeRotation(FRotator(RawNewElevation, 0.f, 0.f));
	//Super::SetWorldRotation(FRotator(RawNewElevation, 0.f, 0.f));
	/*
	if (RelativeRotation.Yaw > 90.f && RelativeRotation.Yaw < 270.f) { CurrentMinEvelvationClamp = BackMinEvelvationClamp; } 
																else { CurrentMinEvelvationClamp = FrontMinEvelvationClamp;}
																*/
	

	return;
}