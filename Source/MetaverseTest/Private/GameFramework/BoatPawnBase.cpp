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
	RandomWaveOffset = FMath::RandRange(-5.0f, 5.0f);
}

void ABoatPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// The Wave Period is the time it takes for a wave to complete a full cycle and
	// is proportional to the speed of the boat. The faster the boat, the longer the wave period.
	const float& WavePeriod = WavePeriodCurve->GetFloatValue(GetSpeedRatio());
	
	// Wave Height is the amplitude of the wave, which is inversely proportional to the speed of the boat.
	// With the boat moving at full speed, the wave height is lower than when the boat is stationary.
	const float& WaveHeight = WaveHeightCurve->GetFloatValue(GetSpeedRatio());
	
	// Now we need to combine these values to get the current wave offset.
	// Wave Definition is the value of the wave at a given point in time and uses the previous values to calculate it.
	const float WavePeriodHeight = WaveDefinitonCurve->GetFloatValue(WaveHeight * FMath::Sin((GetWorld()->GetTimeSeconds() + RandomWaveOffset) / WavePeriod));
	
	TargetBoatWaveOffset = FVector(0.0f, 0.0f, WavePeriodHeight);

	UE_LOG(LogBoatCore, Log, TEXT("WaveHeight: %f"), WaveHeight);
}

// Called to bind functionality to input
void ABoatPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
