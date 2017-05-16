// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_Project.h"
#include "TankTrack.h"
#include "Public/TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throttle = 0.f) {
	//if (Throttle){
	if (!LeftTrack|| !RightTrack) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
		//UE_LOG(LogTemp, Warning, TEXT("I recieved your input at: %f"), Throttle);

}
void UTankMovementComponent::IntendTurnRight(float Throttle = 0.f) {
	//if (Throttle){
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
//	UE_LOG(LogTemp, Warning, TEXT("I recieved your input at: %f"), Throttle);
	//}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("Hi"));
	UE_LOG(LogTemp, Warning, TEXT("%s, MoveVelocity: %s"), *GetOwner()->GetName(),*MoveVelocity.ToString());
}
