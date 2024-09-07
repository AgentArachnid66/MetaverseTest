// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SplineFollowComponent.h"

#include "GameFramework/SplineActorBase.h"
#include "Interfaces/SplineFollowInterface.h"
#include "CustomSplineModule.h"

// Sets default values for this component's properties
USplineFollowComponent::USplineFollowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USplineFollowComponent::StartFollowing()
{	
	// Check if the spline actor is set, this should always be set but we check just in case
	if(!SplineActor.IsValid())
	{
		UE_LOG(LogCustomSplineModule, Warning, TEXT("[%s]::StartFollowing::Spline actor is not valid"), *GetNameSafe(GetOwner()));
		return;
	}

	// Retrieve the spline component from the spline actor
	SplineComponent = SplineActor.Get()->FindComponentByClass<USplineComponent>();

	if(!SplineComponent.IsValid())
	{
		UE_LOG(LogCustomSplineModule, Warning, TEXT("[%s]::StartFollowing::Spline component is not valid"), *GetNameSafe(GetOwner()));
		return;
	}
	
	// Get the distance along the spline at the start location
	const FVector ClosestPoint = SplineComponent->FindLocationClosestToWorldLocation(
		ISplineFollowInterface::Execute_GetActorSplineStartLocation(GetOwner()),
		ESplineCoordinateSpace::World);
	
	// Set the distance to the start location, this is where the actor will start following the spline
	// This is done to ensure that the actor starts at the correct location on the spline
	_Distance = SplineComponent->GetDistanceAlongSplineAtLocation(ClosestPoint, ESplineCoordinateSpace::World);

	// Start the timer to move the actor along the spline
	if(TimerHandle.IsValid())
	{		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Rate, true);
	}
	else
	{
		TimerDelegate.BindUObject(this, &USplineFollowComponent::MoveAlongSpline);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Rate, true);
	}
}

void USplineFollowComponent::StopFollowing()
{
	if(TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		UE_LOG(LogCustomSplineModule, Warning, TEXT("[%s]::StopFollowing::TimerHandle is not valid"), *GetNameSafe(GetOwner()));
	}
}


// Called when the game starts
void USplineFollowComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if(GetOwner()->HasAuthority())
	{
		_SplineTargetPoint = GetOwner()->GetActorLocation();
		_SplineTargetRotation = GetOwner()->GetActorRotation();

		StartFollowing();
	}
	
}

void USplineFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Moves the Owner along the spline and orients it to the spline
	GetOwner()->SetActorLocation(FMath::VInterpTo(GetOwner()->GetActorLocation(), _SplineTargetPoint, DeltaTime, 5), true);
	GetOwner()->SetActorRotation(FMath::RInterpTo(GetOwner()->GetActorRotation(), _SplineTargetRotation, DeltaTime, 5));
}

void USplineFollowComponent::MoveAlongSpline_Implementation()
{
	// verify the spline component is valid
	if(SplineComponent.IsValid())
	{
		// get the next point on the spline
		_SplineTargetPoint = SplineComponent->GetLocationAtDistanceAlongSpline(_Distance, ESplineCoordinateSpace::World);
		_SplineTargetRotation = SplineComponent->GetRotationAtDistanceAlongSpline(_Distance, ESplineCoordinateSpace::World);

		// update the distance
		_Distance += Speed * Rate;
		UE_LOG(LogCustomSplineModule, Log, TEXT("Distance: [%f], Speed: [%f], Rate: [%f]"), _Distance, Speed, Rate);

		if(_Distance >= SplineComponent->GetSplineLength())
		{
			// if the distance is greater than the length of the spline, reset the distance to 0
			_Distance = 0;
			UE_LOG(LogCustomSplineModule, Log, TEXT("Distance is greater than the length of the spline, resetting distance to 0"));
		}
	}
	else
	{
		UE_LOG(LogCustomSplineModule, Warning, TEXT("[%s]::MoveAlongSpline::Spline component is not valid"), *GetNameSafe(GetOwner()));
	}
	
}
