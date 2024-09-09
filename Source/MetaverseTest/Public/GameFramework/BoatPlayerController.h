// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoatPlayerController.generated.h"


class UInputAction;
struct FInputActionValue;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class METAVERSETEST_API ABoatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABoatPlayerController();
	virtual void BeginPlay() override;


protected:
	/**
	* @brief Input mapping context that defines how input is mapped to actions.
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* BoatInputMapping;

	/**
	 * @brief Input action that handles movement-related inputs (e.g., forward thrust, steering).
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	/**
	 * @brief Triggered when a movement input action is detected.
	 * @param InputActionValue The value associated with the movement input action (e.g., strength or direction).
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnMovementActionTriggered(const FInputActionValue& InputActionValue);
};

