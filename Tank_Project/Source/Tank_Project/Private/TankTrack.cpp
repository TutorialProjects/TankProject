// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {


}
void UTankTrack::SetThrottle(float inputThrottle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle+ inputThrottle, -1.f, 1.f);
	//CurrentThrottle = inputThrottle;
}
void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * MaxDrivingForce *CurrentThrottle;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	ForceLocation.X += 50.f;
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
//	UE_LOG(LogTemp,Warning,TEXT("I was hit"))
	ApplyAntiForce();
	CurrentThrottle = 0;
}
void UTankTrack::ApplyAntiForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float RightVelocityRate = FVector::DotProduct(GetRightVector(), GetComponentVelocity());  //slippage speed
	FVector RightVelocityModifierOverDeltaTime = -RightVelocityRate / DeltaTime * GetRightVector(); // correction acceleration
	UStaticMeshComponent* TankRootComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector AntiForce = (TankRootComp->GetMass() * RightVelocityModifierOverDeltaTime) / 2;
	TankRootComp->AddForce(AntiForce);
}