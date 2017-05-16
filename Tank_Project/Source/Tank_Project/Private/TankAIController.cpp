// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankPawn.h"
#include "Public/TankAIController.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();


}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		auto PlayerTankPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		PlayerTankPawn = Cast<ATankPawn>(PlayerTankPawn);
		auto AIPawn = Cast<ATankPawn>(GetPawn());
		if (PlayerTankPawn &&AIPawn) {
			
			AIPawn->AimAt(PlayerTankPawn->GetActorLocation());
			AIPawn->Fire();
			MoveToActor(PlayerTankPawn, AcceptanceRadius);
		}

}
