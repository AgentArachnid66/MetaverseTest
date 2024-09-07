// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "BoatPawnBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoatMoveInputDelegate, float, Value);

UCLASS()
class METAVERSETEST_API ABoatPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoatPawnBase();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void ThrustForward(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void SteerBoat(float Value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Boat Movement")
	void BrakeBoat(float Value);
	
	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	FORCEINLINE UFloatingPawnMovement* GetFloatingMovementComponent() const { return MovementComponent; }

	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	FORCEINLINE float GetSteerInput() const { return SteerInput; }


	UPROPERTY(BlueprintAssignable, Category = "Boat Movement")
	FBoatMoveInputDelegate OnSteerInputUpdated;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AsyncPhysicsTickActor(float DeltaTime, float SimTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	float RawSteeringInput = 0.0f;

	float SteerInput = 0.0f;
	float TargetSteerInput = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	float SteerInterpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	float TargetSteerInterpSpeed;
};
