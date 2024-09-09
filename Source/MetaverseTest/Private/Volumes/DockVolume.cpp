// Fill out your copyright notice in the Description page of Project Settings.


#include "Volumes/DockVolume.h"
#include "Interfaces/DockTargetInterface.h"
#include "MetaverseTest/MetaverseTest.h"

void ADockVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADockVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Check if the OtherActor is valid
	if(!IsValid(OtherActor))
	{
		UE_LOG(LogBoatCore, Warning, TEXT("DockVolume: Actor is not valid"));
		return;
	}
	
	// Check if the OtherActor implements the IDockTarget interface
	if(!OtherActor->GetClass()->ImplementsInterface(UDockTargetInterface::StaticClass()))
	{
		UE_LOG(LogBoatCore, Warning, TEXT("DockVolume: Actor [%s] does not implement IDockTargetInterface"), *GetNameSafe(OtherActor));
		return;
	}

	// Start the docking process
	IDockTargetInterface::Execute_OnDockStart(OtherActor);

	// Creates a timer to complete the docking process
	FTimerHandle& TimerHandle = DockTimers.FindOrAdd(OtherActor);
	GetWorldTimerManager().SetTimer(TimerHandle, [this, OtherActor]()
	{
		if(!IsValid(OtherActor))
		{
			UE_LOG(LogBoatCore, Warning, TEXT("DockVolume: Actor is not valid, docking process cannot be completed"));
			return;
		}
		
		// Complete the docking process
		IDockTargetInterface::Execute_OnDockComplete(OtherActor);
				
	}, DockTime, false);

	// Adds the timer to the map
	DockTimers.Add(OtherActor, TimerHandle);
}

void ADockVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	// Check if the OtherActor is valid
	if(!IsValid(OtherActor))
	{
		UE_LOG(LogBoatCore, Warning, TEXT("DockVolume: Actor is not valid"));
		return;
	}
	
	// Check if the OtherActor implements the IDockTarget interface
	if(!OtherActor->GetClass()->ImplementsInterface(UDockTargetInterface::StaticClass()))
	{
		UE_LOG(LogBoatCore, Warning, TEXT("DockVolume: Actor [%s] does not implement IDockTargetInterface"), *GetNameSafe(OtherActor));
		return;
	}


	// Clear the timer
	FTimerHandle TimerHandle = DockTimers.FindRef(OtherActor);
	if(TimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		TimerHandle.Invalidate();
					
		// Cancel the docking process
		IDockTargetInterface::Execute_OnDockCancel(OtherActor);
	}
}
