// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Tank_Projectile.h"


// Sets default values
ATank_Projectile::ATank_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent= CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Component"));
	MovementComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void ATank_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATank_Projectile::LaunchProjectile(float speed) {
	//MovementComponent->InitialSpeed = speed;
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	MovementComponent->Activate();
}

