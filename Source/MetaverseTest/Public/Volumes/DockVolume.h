// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "DockVolume.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSETEST_API ADockVolume : public AVolume
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	/**
	 * @brief How long it takes a boat to dock
	 */
	UPROPERTY(EditAnywhere, Category = "Dock")
	float DockTime = 1.0f;

	// Map of actors and their timers, using a weak pointer to avoid this class
	// preventing the actor from being garbage collected if it is destroyed
	TMap<TWeakObjectPtr<AActor>, FTimerHandle> DockTimers;
};
