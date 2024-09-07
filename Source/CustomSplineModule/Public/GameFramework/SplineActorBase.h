// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "SplineActorBase.generated.h"

UCLASS()
class CUSTOMSPLINEMODULE_API ASplineActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineActorBase();

	UFUNCTION(BlueprintPure, Category = "Spline")
	USplineComponent* GetSplineComponent() const { return SplineComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
	USplineComponent* SplineComponent;
};
