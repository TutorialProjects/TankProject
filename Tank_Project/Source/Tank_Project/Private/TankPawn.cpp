// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankPawn.h"


// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//UE_LOG(LogTemp,Warning, TEXT("Tank Pawn C++ Construction script ran"))
//	TankAimingComponent = CreateDefaultSubobject<UTankComponentAiming>(FName("Aiming Component"));



}




// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void ATankPawn::AimAt(FVector HitLocation) {
	// LOG OUT THE DISTANCE AWAY IN EVERYTHING
	/*
	FVector CurrentLocation = GetActorLocation();
	FVector Difference = HitLocation - CurrentLocation;
	float MetersAway = (Difference.Size() / 100);
	float KiloMetersAway = (MetersAway / 1000);
	float FeetAway = (MetersAway*3.28084);
	float MilesAway = (FeetAway*0.000189394);
	UE_LOG(LogTemp, Warning, TEXT("Distance Away:| Meters: %f| |Feet: %f| |Miles: %f| |Kilometers: %f "),
		MetersAway, FeetAway, MilesAway, KiloMetersAway)
		*/
	/*old logs
	FVector CurrentLocation = GetActorLocation();
	FVector Difference = HitLocation - CurrentLocation;
	float MetersAway = (Difference.Size() / 100);
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s, Distance: %f meters"), *GetName(), *HitLocation.ToString(), MetersAway)
	*/
	//if (!TankAimingComponent) { return; }
	//TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

//}


