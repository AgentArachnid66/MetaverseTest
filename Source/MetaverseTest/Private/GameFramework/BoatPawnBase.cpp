// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/BoatPawnBase.h"

#include "MetaverseTest/MetaverseTest.h"

// Sets default values
ABoatPawnBase::ABoatPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

}

void ABoatPawnBase::ThrustForward_Implementation(float Value)
{
	UE_LOG(LogBoatCore, Verbose, TEXT("ThrustForward: %f"), Value);
}

void ABoatPawnBase::SteerBoat_Implementation(float Value)
{
	UE_LOG(LogBoatCore, Verbose, TEXT("SteerBoat: %f"), Value);
	RawSteeringInput = Value;
}

void ABoatPawnBase::BrakeBoat_Implementation(float Value)
{
	UE_LOG(LogBoatCore, Verbose, TEXT("BrakeBoat: %f"), Value);
}


float ABoatPawnBase::GetSpeedRatio() const
{
	return GetMovementComponent()->Velocity.Size() / GetMovementComponent()->GetMaxSpeed();
}

// Called when the game starts or when spawned
void ABoatPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABoatPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ABoatPawnBase::AsyncPhysicsTickActor(float DeltaTime, float SimTime)
{
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);

	// Interpolate the steering input
	TargetSteerInput = FMath::FInterpTo(TargetSteerInput, RawSteeringInput, DeltaTime, TargetSteerInterpSpeed);
	UE_LOG(LogBoatCore, Log, TEXT("TargetSteerInput: %f"), TargetSteerInput);
	SteerInput = FMath::FInterpTo(SteerInput, TargetSteerInput, DeltaTime, SteerInterpSpeed);
	UE_LOG(LogBoatCore, Log, TEXT("SteerInput: %f"), SteerInput);
	OnSteerInputUpdated.Broadcast(SteerInput);
}
