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
	// Sets default values for this component's properties
	USplineFollowComponent();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Spline Follow")
	void StartFollowing();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Spline Follow")
	void StopFollowing();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "Spline Follow")
	void MoveAlongSpline();


	/**
	 * @brief The rate at which the actor moves along the spline. The rate is the time step at which the actor moves along the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow")
	float Rate = 1.0f;

	/**
	 * @brief The speed at which the actor moves along the spline.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow")
	float Speed = 100.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Follow", meta=(MustImplement="SplineRetrievalInterface"))
	TSoftObjectPtr<AActor> SplineActor;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TWeakObjectPtr<USplineComponent> SplineComponent;

	private:

	float _Distance;
	FVector _SplineTargetPoint = FVector::ZeroVector;
	FRotator _SplineTargetRotation = FRotator::ZeroRotator;
};
