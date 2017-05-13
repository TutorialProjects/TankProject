// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankPlayerController.h"
#define OUT



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

	 FVector HitLocation;
	 if (GetSightRayHitLocation(HitLocation)) {
		 GetControlledTank()->AimAt(HitLocation);

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
			GetLookVectorHitLocation(LookDirection, outHitLocation);
		};
	 
	// UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString());
	 //line trace by channel
	 // if hit, set outlocation to the hitcomponent.location, then return true
	 // if HitResult.HitComponent == false, do nothing and return false
	 return true;
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
		 outHitLocation = HitResult.Location;
		 return true;
	 }
	 outHitLocation = FVector(0.f); //<- just in case u forget to check
	 return false;
 }