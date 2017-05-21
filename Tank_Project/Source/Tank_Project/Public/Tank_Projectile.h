// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tank_Projectile.generated.h"

UCLASS()
class TANK_PROJECT_API ATank_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATank_Projectile();
	UPROPERTY(EditDefaultsOnly, Category = "COMPONENTS")
	UProjectileMovementComponent* MovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "COMPONENTS")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "COMPONENTS")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "COMPONENTS")
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "COMPONENTS")
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditAnywhere)
	float DestroyDelay = 1.f;
	UPROPERTY(EditAnywhere)
	float TankDamage = 50.f;

	void LaunchProjectile(float speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	//void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit); // OnActorHit signature
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DestroyProjectile();
	
	
};
