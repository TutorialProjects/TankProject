// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankComponentAiming.h"
#include "TankBarrelMeshComp.h"


// Sets default values for this component's properties
UTankComponentAiming::UTankComponentAiming()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankComponentAiming::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankComponentAiming::SetBarrelReference(UTankBarrelMeshComp* BarrelToSet) {
	Barrel = BarrelToSet;
}
// Called every frame
void UTankComponentAiming::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankComponentAiming::AimAt(FVector AimLocation, float LaunchSpeed) {
	//FVector CurrentLocation = GetOwner()->GetActorLocation();
	if (!Barrel) { return; }

	FVector outLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	
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
			true);
	if (bHaveAimSolution && AimLocation != FVector(0.f)) {
		FVector SuggestedDirection = outLaunchVelocity.GetSafeNormal();
	//	UE_LOG(LogTemp, Warning, TEXT("%s Suggested Direction: %s Suggested Velocity %s"), *GetOwner()->GetName(), *AimDirection.ToString(), *outLaunchVelocity.ToString())
			MoveBarrelTowards(SuggestedDirection);
			auto time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%s %f Aim solution found for world location %s. Suggested Direction: %s .  Suggested Veolocity: %s"), *GetOwner()->GetName(), time, *AimLocation.ToString(),*SuggestedDirection.ToString(), *outLaunchVelocity.ToString())
	}
	else if (AimLocation == FVector(0.f)) {
		UE_LOG(LogTemp, Warning, TEXT("%s %f Did not input an end location greater then 0.f,0.f,0.f"), *GetOwner()->GetName(), GetWorld()->GetTimeSeconds())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s %f No valid suggested velocity found"), *GetOwner()->GetName(), GetWorld()->GetTimeSeconds())
	}
		
	if (Barrel) {
		FVector BarrelLocation = Barrel->GetComponentLocation();
		FVector Difference = AimLocation - BarrelLocation;
		float MetersAway = (Difference.Size() / 100);
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at %f m/s from %f m away"), *GetOwner()->GetName(), LaunchSpeed, MetersAway)
	}
	return;
}

void UTankComponentAiming::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRot = AimRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("BarrelRot: %s  AimRot: %s"), *BarrelRotator.ToString(), *AimRotator.ToString())
		// work out difference between current barrel rotatio, and 
		Barrel->Elevate(5);
	return;
}

