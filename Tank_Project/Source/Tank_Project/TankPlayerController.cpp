// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankComponentAiming.h"
#include "TankPawn.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

 void ATankPlayerController::BeginPlay() {
	 Super::BeginPlay();
	 if (!GetPawn()) { return; }
	//AimingComponent = GetControlledTank()->FindComponentByClass<UTankComponentAiming>();
	 UTankComponentAiming* AimingComponent = GetPawn()->FindComponentByClass<UTankComponentAiming>();
	 if (!AimingComponent) { return; }
	 FoundAimingComponent(AimingComponent); //fills in the ufunction output params for blueprintimplementable
	 

}
 
 void ATankPlayerController::SetPawn(APawn* InPawn)
 {
	 Super::SetPawn(InPawn);
	 if (InPawn)
	 {
		 auto PossessedTank = Cast<ATankPawn>(InPawn);
		 if (!ensure(PossessedTank)) { return; }

		 PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);

	 }
 }
 void ATankPlayerController::OnPossessedTankDeath() {
	 UE_LOG(LogTemp, Warning, TEXT("He Deaded Me"))
		 if (GetPawn()) {
			 StartSpectatingOnly();
		// Destroy();
		 }


 }
 
 void ATankPlayerController::AimTowardsCrosshair() {
	 if (!GetPawn()) { return; }
	 auto AimingComponent = GetPawn()->FindComponentByClass<UTankComponentAiming>();
	 if (!AimingComponent) { return; }

	 FVector HitLocation;
	 bool bGotHitLocation =GetSightRayHitLocation(HitLocation);

	 if (bGotHitLocation) {
	
			 AimingComponent->AimAt(HitLocation);	 

		 // LOG OUT THE DISTANCE AWAY IN METERS
		 /*
		 FVector CurrentLocation = GetPawn()->GetActorLocation();
		 FVector Difference = HitLocation - CurrentLocation;
		 float MetersAway = (Difference.Size() / 100);
		 float KiloMetersAway = (MetersAway / 1000);
		 float FeetAway = (MetersAway*3.28084);
		 float MilesAway = (FeetAway*0.000189394);
		 UE_LOG(LogTemp, Warning, TEXT("Distance Away:| Meters: %f| |Feet: %f| |Miles: %f| |Kilometers: %f "),
			 MetersAway, FeetAway, MilesAway, KiloMetersAway)
			 */
	 }


	 return;
 }

 bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const{
	 // get player forward vector
	 //GetWorld()->GetFirstPlayerController()->GetPawn();
	 int32 ViewportSizeX, ViewportSizeY; /*=*/
	 /*OUT*/ GetViewportSize(ViewportSizeX, ViewportSizeY);

	 FVector2D ScreenLocation((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrossHairYLocation));
	 FVector LookDirection; /*=*/
	 if (GetLookDirection(ScreenLocation, LookDirection))
		{
			return GetLookVectorHitLocation(LookDirection, outHitLocation);
		};
	 
	// UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString());
	 //line trace by channel
	 // if hit, set outlocation to the hitcomponent.location, then return true
	 // if HitResult.HitComponent == false, do nothing and return false
	 return false;
 }
 bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector &outLookDirection) const{
	 FVector WorldCameraLocation; //to be discarded
	 return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldCameraLocation, outLookDirection);
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction, FVector &outHitLocation) const{
	 FHitResult HitResult;
	 auto StartLocation = PlayerCameraManager->GetCameraLocation();
	 auto EndLocation = StartLocation + (Direction*LineTraceRange);
	 if (GetWorld()->LineTraceSingleByChannel(
		 HitResult,
		 StartLocation,
		 EndLocation,
		 ECollisionChannel::ECC_Visibility))
	 {
		// UE_LOG(LogTemp,Warning,TEXT("The HitResult: %s"), *HitResult.Location.ToString())
		 outHitLocation = HitResult.Location;
		 return true;
	 }
	 outHitLocation = FVector(0.f); //<- just in case u forget to check
	// UE_LOG(LogTemp, Warning, TEXT("the check: %s"), *HitResult.Location.ToString())
	 return false;
 }