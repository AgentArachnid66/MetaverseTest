// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SplineFollowComponent.generated.h"


class USplineComponent;
class ASplineActorBase;
/**
 * The SplineFollowComponent is a component that allows an actor to follow a spline. It holds a reference to a spline and moves the owning
 * actor along the spline at a given speed. 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMSPLINEMODULE_API USplineFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/**
	 * @brief Constructor: Sets default values for this component's properties.
	 */
	USplineFollowComponent();

	/**
	 * @brief Starts following the spline.
	 * This function is only callable by the authority (server or owning client).
	 */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Spline Follow")
	void StartFollowing();

	/**
	 * @brief Stops following the spline.
	 * This function is only callable by the authority (server or owning client).
	 */
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Spline Follow")
	void StopFollowing();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Moves the actor along the spline. 
	 * This function is only callable by the authority (server or owning client).
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Spline Follow")
	void MoveAlongSpline();
	
	/**
	 * @brief The rate at which the actor moves along the spline. 
	 * The rate determines the time step at which the actor moves.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow")
	float Rate = 1.0f;

	/**
	 * @brief The speed at which the actor moves along the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow")
	float Speed = 100.0f;

	/**
	 * @brief Reference to the spline actor that this component follows.
	 * This actor must implement the SplineRetrievalInterface.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow", meta=(MustImplement="SplineRetrievalInterface"))
	TSoftObjectPtr<AActor> SplineActor;

	/**
	 * @brief Handle for the timer that manages the movement along the spline.
	 */
	FTimerHandle TimerHandle;

	/**
	 * @brief Delegate for the timer that manages the movement logic.
	 */
	FTimerDelegate TimerDelegate;

	/**
	 * @brief Weak pointer to the spline component of the spline actor.
	 */
	TWeakObjectPtr<USplineComponent> SplineComponent;

private:
	/**
	 * @brief The current distance along the spline that the actor has moved.
	 */
	float _Distance;

	/**
	 * @brief The target point on the spline that the actor is moving towards.
	 */
	FVector _SplineTargetPoint = FVector::ZeroVector;

	/**
	 * @brief The target rotation of the actor when moving along the spline.
	 */
	FRotator _SplineTargetRotation = FRotator::ZeroRotator;

};
