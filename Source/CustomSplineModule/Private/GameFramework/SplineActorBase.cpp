// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SplineActorBase.h"

// Sets default values
ASplineActorBase::ASplineActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

}

// Called when the game starts or when spawned
void ASplineActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

