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
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* BoatInputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnMovementActionTriggered(const FInputActionValue& InputActionValue);
};

