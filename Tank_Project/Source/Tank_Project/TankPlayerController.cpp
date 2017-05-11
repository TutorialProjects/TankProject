// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankPlayerController.h"




ATankPawn* ATankPlayerController::GetControlledTank() const {

	return Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

 void ATankPlayerController::BeginPlay() {
	 Super::BeginPlay();
	 auto ControlledTank = GetControlledTank();
	 if (ControlledTank) {
		 UE_LOG(LogTemp, Warning, TEXT("Player Pawn Name: %s"), *(GetControlledTank()->GetName()))
	 }
	 else {
		 UE_LOG(LogTemp, Warning, TEXT("Player Pawn is not a tank"))
	 }

}
 void ATankPlayerController::AimTowardsCrosshair() {

	 if (!GetControlledTank()) { return; }
	 return;
 }
