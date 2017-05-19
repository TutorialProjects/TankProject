// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankBarrelMeshComp.h"
#include "TankTurret.h"
#include "Tank_Projectile.h"
#include "TankComponentAiming.h"



// Sets default values for this component's properties
UTankComponentAiming::UTankComponentAiming()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankComponentAiming::BeginPlay()
{
	//Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("Aiming comp begin play"))
	// ...
	
}
// Called every frame
void UTankComponentAiming::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	UE_LOG(LogTemp, Warning, TEXT("Aiming comp ticking"))
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
			FiringState = EFiringStatus::Reloading;
		}
		else if (IsBarrelMoving()) { FiringState = EFiringStatus::Locked; }
		else{ FiringState = EFiringStatus::Aiming; }
}

bool UTankComponentAiming::IsBarrelMoving() {
	if (!TankBarrel) { return false; }
	if (((TankBarrel->GetForwardVector()).Equals(GlobalAimDirection, 0.1))) { return true; }
	else {
		return false;
	}

}

void UTankComponentAiming::SetBarrelReference(UTankBarrelMeshComp* BarrelToSet) {
	if (!BarrelToSet) { return; }
	TankBarrel = BarrelToSet;
}
void UTankComponentAiming::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	TankTurret = TurretToSet;
}


void UTankComponentAiming::AimAt(FVector AimLocation) {
	//FVector CurrentLocation = GetOwner()->GetActorLocation();
	if (!TankBarrel || !TankTurret) { return; }

	FVector outLaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Muzzle"));
	
	FCollisionResponseParams params;
	TArray<AActor*> ActorList;
	ActorList.Add(GetOwner());
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			outLaunchVelocity,
			StartLocation,
			AimLocation,
			LaunchSpeed,
			false,
			0.f,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			ActorList,
			DebugLineOption);
	if (bHaveAimSolution && AimLocation != FVector(0.f)) {
		FVector SuggestedDirection = outLaunchVelocity.GetSafeNormal();
		GlobalAimDirection = SuggestedDirection;
	//	UE_LOG(LogTemp, Warning, TEXT("%s Suggested Direction: %s Suggested Velocity %s"), *GetOwner()->GetName(), *AimDirection.ToString(), *outLaunchVelocity.ToString())
			MoveBarrelTowards(SuggestedDirection);
			MoveTurretTowards(SuggestedDirection);
			auto time = GetWorld()->GetTimeSeconds();
		//	UE_LOG(LogTemp, Warning, TEXT("%s %f Aim solution found for world location %s. Suggested Direction: %s .  Suggested Veolocity: %s"), *GetOwner()->GetName(), time, *AimLocation.ToString(),*SuggestedDirection.ToString(), *outLaunchVelocity.ToString())
	}
	else if (AimLocation == FVector(0.f)) {
	//	UE_LOG(LogTemp, Warning, TEXT("%s %f Did not input an end location greater then 0.f,0.f,0.f"), *GetOwner()->GetName(), GetWorld()->GetTimeSeconds())
	}
	else {
	//	UE_LOG(LogTemp, Warning, TEXT("%s %f No valid suggested velocity found"), *GetOwner()->GetName(), GetWorld()->GetTimeSeconds())
	}
		
	if (TankBarrel) {
		FVector BarrelLocation = TankBarrel->GetComponentLocation();
		FVector Difference = AimLocation - BarrelLocation;
		float MetersAway = (Difference.Size() / 100);
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at %f m/s from %f m away"), *GetOwner()->GetName(), LaunchSpeed, MetersAway)
	}
	return;
}

void UTankComponentAiming::MoveBarrelTowards(FVector AimDirection)
{
	if (!TankBarrel || !TankTurret) { return; } // <-this protection is unneeded if you dont call it arbitrarily
	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRot = AimRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("BarrelRot: %s  AimRot: %s"), *BarrelRotator.ToString(), *AimRotator.ToString())
		// work out difference between current barrel rotatio, and 
	TankBarrel->Elevate(DeltaRot.Pitch);
	return;
}

void UTankComponentAiming::MoveTurretTowards(FVector AimDirection)
{
	if (!TankBarrel || !TankTurret) { return; }// <-this protection is unneeded if you dont call it arbitrarily
	FRotator TurretRotator = TankTurret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRot = AimRotator - TurretRotator;
	//UE_LOG(LogTemp, Warning, TEXT("BarrelRot: %s  AimRot: %s"), *BarrelRotator.ToString(), *AimRotator.ToString())
	// work out difference between current barrel rotatio, and 
	
	TankTurret->Turn(DeltaRot.Yaw);
	return;
}
void UTankComponentAiming::Initialize(UTankBarrelMeshComp* barrelComp, UTankTurret* turretComp)
{
	TankBarrel = barrelComp;
	TankTurret = turretComp;

}

UTankBarrelMeshComp* UTankComponentAiming::GetTankBarrel() {

	return TankBarrel;
}

void UTankComponentAiming::Fire() {
	
	

	if (FiringState != EFiringStatus::Reloading)
	{
		//UE_LOG(LogTemp, Warning, TEXT("FIRE!"))
			if (!ensure(TankBarrel)) { return; }
			if (!ensure(Tank_Projectile_VersionReference)) { return; }
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
		if (TankShell) { TankShell->LaunchProjectile(LaunchSpeed); }
		LastFireTime = FPlatformTime::Seconds();
	}

}


