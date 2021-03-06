// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankComponentAiming.h"
#include "TankPawn.h" //so we can implement on death
#include "Public/TankAIController.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();


}
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATankPawn>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	}
}
void ATankAIController::OnPossessedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Deaded 'Em"))
		if (GetPawn()) {
			GetPawn()->DetachFromControllerPendingDestroy();

			Destroy();
		}
	

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
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}


}
