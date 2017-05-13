// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankAIController.h"


ATankPawn* ATankAIController::GetControlledTankPawn() const {

	return Cast<ATankPawn>(GetPawn());
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
		//UE_LOG(LogTemp, Warning, TEXT("TankAi controller detected player tank: %s"), *(PlayerTank->GetName()))
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("TankAi Controller couldn't find a player tank in the level."))
	}
	
	
	auto ControlledTank = GetControlledPawn();
	if (ControlledTank) {
		//UE_LOG(LogTemp, Warning, TEXT("AI Pawn Name: %s"), *(ControlledTank->GetName()))
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("AI Pawn is not possesing any type of pawn."))
	}

}

ATankPawn* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATankPawn>(PlayerPawn);
//	return Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetControlledTankPawn() && GetPlayerTank())
	{
		GetControlledTankPawn()->AimAt(GetPlayerTank()->GetActorLocation());
	}

	/* // this was included as a debug
	if (Super::GetPawn()) {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn Name: %s"), *(Super::GetPawn()->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Pawn Not Found."))
	}
	*/


}
