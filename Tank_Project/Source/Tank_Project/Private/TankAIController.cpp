// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankAIController.h"


APawn* ATankAIController::GetControlledPawn() const {

	return Cast<APawn>(GetPawn());
}


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	if (Super::GetPawn()) {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn Name: %s"), *(Super::GetPawn()->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn Not Found."))
	}
	ATankPawn* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("I found you, %s"), *(PlayerTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Well, Double Fuck."))
	}
	/*
	auto ControlledTank = GetControlledPawn();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn Name: %s"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn is not possesing any type of pawn."))
	}
*/
}

ATankPawn* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATankPawn>(PlayerPawn);
//	return Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

