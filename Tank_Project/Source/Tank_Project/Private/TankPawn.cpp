// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Public/TankComponentAiming.h"
#include "Public/TankBarrelMeshComp.h"
#include "Public/TankTurret.h"
#include "Public/Tank_Projectile.h"
#include "Public/TankPawn.h"


// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp,Warning, TEXT("Tank Pawn C++ Construction script ran"))
	TankAimingComponent = CreateDefaultSubobject<UTankComponentAiming>(FName("Aiming Component"));



}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Tank Pawn C++ Begin Play function called"))
		Super::BeginPlay();
	if (TankAimingComponent) {
		if (TankAimingComponent->GetTankBarrel())
		{
			TankBarrel = TankAimingComponent->GetTankBarrel();
		}
	}
}


// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::AimAt(FVector HitLocation) {
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
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	return;
}
void ATankPawn::Fire() {
	if (!ensure(TankBarrel)) { return; }
	bool isReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds);
	if (isReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("FIRE!"))

			FVector ProjectileSpawnLoc;
		FRotator ProjectileSpawnRot;
		//TankBarrel->GetSocketWorldLocationAndRotation(FName("Muzzle"), ProjectileSpawnLoc, ProjectileSpawnRot);
		ProjectileSpawnLoc = TankBarrel->GetSocketLocation(FName("Muzzle"));
		ProjectileSpawnRot = TankBarrel->GetSocketRotation(FName("Muzzle"));
		//	FTransform ProjectileSpawnTrans = TankBarrel->GetSocketTransform(FName("Muzzle"));
		//GetWorld()->SpawnActor<>();
		if (!Tank_Projectile_VersionReference) { return; }
		//	Tank_Projectile_BP->SetInitialSpeed(LaunchSpeed);
		ATank_Projectile* TankShell = GetWorld()->SpawnActor<ATank_Projectile>(Tank_Projectile_VersionReference, ProjectileSpawnLoc, ProjectileSpawnRot);
		TankShell->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	return;
}
