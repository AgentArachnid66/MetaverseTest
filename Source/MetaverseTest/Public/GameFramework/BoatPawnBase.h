// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "BoatPawnBase.generated.h"

UCLASS()
class METAVERSETEST_API ABoatPawnBase : public APawn
{
	GENERATED_BODY()
	/**
	 * @brief Applies forward thrust to the boat.
	 * @param Value The strength or amount of thrust to apply (can be positive or negative but negative results in braking).
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void ThrustForward(float Value);

	/**
	 * @brief Steers the boat in a specified direction.
	 * @param Value The direction and magnitude of the steering input (positive for right, negative for left).
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void SteerBoat(float Value);

	/**
	 * @brief Applies braking force to the boat to slow it down or stop.
	 * @param Value The strength of the braking force (higher value means stronger braking).
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void BrakeBoat(float Value);

	/**
	 * @brief Retrieves the floating movement component responsible for the boat's movement.
	 * @return A pointer to the UFloatingPawnMovement component.
	 */
	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	FORCEINLINE UFloatingPawnMovement* GetFloatingMovementComponent() const { return MovementComponent; }

	/**
	 * @brief Gets the current speed ratio of the boat, which can be used to evaluate how fast the boat is moving.
	 * @return The speed ratio as a float.
	 */
	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	float GetSpeedRatio() const;

protected:
	/**
	 * @brief Called when the game starts or when the boat is spawned in the game world.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Called every frame to update the boat's state (movement, steering, etc.).
	 * @param DeltaTime The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Binds the player input to boat functionality, such as steering and thrust.
	 * @param PlayerInputComponent The input component that handles player inputs.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Variables

	/**
	 * @brief The component responsible for handling the boat's movement.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	/**
	 * @brief A curve defining how the height of the waves affects the boat's movement.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WaveHeightCurve;

	/**
	 * @brief A curve defining the time between waves, influencing the boat's interaction with the water.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WavePeriodCurve;

	/**
	 * @brief A curve defining the shape or characteristics of the waves the boat interacts with.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WaveDefinitonCurve;

	/**
	 * @brief Retrieves the boat's current offset relative to the target wave position.
	 * @return The wave offset as a FVector.
	 */
	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	FORCEINLINE FVector GetTargetBoatWaveOffset() const { return TargetBoatWaveOffset; }

private:
	/**
	 * @brief The boat's current target wave offset (positioning relative to waves).
	 */
	FVector TargetBoatWaveOffset;

	/**
	 * @brief A random offset value applied to simulate variable wave interaction.
	 */
	float RandomWaveOffset;
};
