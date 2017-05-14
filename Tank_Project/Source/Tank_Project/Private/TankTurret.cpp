// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankTurret.h"




void UTankTurret::Turn(float scaleMultiplier = 1) {
	scaleMultiplier = FMath::Clamp(scaleMultiplier, -1.f, 1.f);
	auto TurnAmount = (MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds)) * scaleMultiplier;
	auto RawNewTurn = Super::RelativeRotation.Yaw + TurnAmount;
	Super::SetRelativeRotation(FRotator(0.f, RawNewTurn,0.0f ));

	return;
}