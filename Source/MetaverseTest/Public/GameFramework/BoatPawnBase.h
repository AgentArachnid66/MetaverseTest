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
	float GetSpeedRatio() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WaveHeightCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WavePeriodCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boat Movement")
	UCurveFloat* WaveDefinitonCurve;
	
	UFUNCTION(BlueprintPure, Category = "Boat Movement")
	FORCEINLINE FVector GetTargetBoatWaveOffset() const { return TargetBoatWaveOffset; }
	
private:

	FVector TargetBoatWaveOffset;
	float RandomWaveOffset;
};
