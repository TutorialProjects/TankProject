// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankComponentAiming.h"


// Sets default values for this component's properties
UTankComponentAiming::UTankComponentAiming()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankComponentAiming::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankComponentAiming::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
			params,
			ActorList,
			true);
	if (bHaveAimSolution) {
		FVector AimDirection = outLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s Suggested Direction: %s Suggested Velocity %s"), *GetOwner()->GetName(), *AimDirection.ToString(), *outLaunchVelocity.ToString())
	}
		
	if (Barrel) {
		FVector BarrelLocation = Barrel->GetComponentLocation();
		FVector Difference = AimLocation - BarrelLocation;
		float MetersAway = (Difference.Size() / 100);
		//UE_LOG(LogTemp, Warning, TEXT("%s Firing at %f m/s from %f m away"), *GetOwner()->GetName(), LaunchSpeed, MetersAway)
	}
	return;
}

