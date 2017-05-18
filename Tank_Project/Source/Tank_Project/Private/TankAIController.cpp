// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankComponentAiming.h"
#include "Public/TankAIController.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();


}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		auto PlayerTank= GetWorld()->GetFirstPlayerController()->GetPawn();
		auto ControlledTank = GetPawn();
		if (!(PlayerTank && ControlledTank)) { return; }	

		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = ControlledTank->FindComponentByClass<UTankComponentAiming>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//TODO fix firing
		//ControlledTank->Fire();


}
