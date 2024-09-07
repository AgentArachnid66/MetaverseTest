// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SplineFollowInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USplineFollowInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CUSTOMSPLINEMODULE_API ISplineFollowInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Maybe not the best name, but this function is used to get the start location of the spline.
	 * This is used to set the actor's location to the start of the spline, as many different actors may have different requirements
	 * for the offset applied when starting to follow the spline.
	 * @return 
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, BlueprintCallable, Category = "Spline Follow")
	FVector GetActorSplineStartLocation() const;
};
