// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "Tank_Projectile.h"


// Sets default values
ATank_Projectile::ATank_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = 0;
	MovementComponent= CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Component"));
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Effect"));
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Effect"));
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionMesh->OnComponentHit.AddDynamic(this, &ATank_Projectile::OnHit);
	//OnActorHit.AddDynamic(this, &ATank_Projectile::OnHit);
	
//	LaunchBlast->SetupAttachment(CollisionMesh);
	
}

// Called when the game starts or when spawned
void ATank_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	//ImpactBlast->OnComponentHit.AddDynamic(this, &ATank_Projectile::OnHit);
	
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

void ATank_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp,Error,TEXT("%s hit"),*GetName())
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	
	//SetRootComponent(ImpactBlast);
	//CollisionMesh->DestroyComponent();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATank_Projectile::DestroyProjectile, DestroyDelay, false);
	
	UGameplayStatics::ApplyRadialDamage(this, TankDamage,GetActorLocation(),ExplosionForce->Radius,UDamageType::StaticClass(), TArray<AActor*>());
	//Destroy();
}


/*
void ATank_Projectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	// OnActorHit signature
}
*/
void ATank_Projectile::DestroyProjectile() {
	Destroy();

}
