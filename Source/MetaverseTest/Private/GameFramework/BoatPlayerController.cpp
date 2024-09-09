// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/BoatPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MetaverseTest/MetaverseTest.h"

ABoatPlayerController::ABoatPlayerController()
{
	
}

void ABoatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	if(!IsLocalController())
	{
		UE_LOG(LogBoatCore, Error, TEXT("[%s] Not a local controller, cannot bind input"), *GetNameSafe(this));
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
 	Subsystem->AddMappingContext(BoatInputMapping, 0);
	
	// Get the Pawn's input component
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetPawn()->InputComponent);
	checkf(EnhancedInputComponent, TEXT("Pawn does not have an EnhancedInputComponent"));

	// Need both Triggered and Completed events to handle continuous input, and for when the input has been released respectively.
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ABoatPlayerController::OnMovementActionTriggered);
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Completed, this, &ABoatPlayerController::OnMovementActionTriggered);
	
}

void ABoatPlayerController::OnMovementActionTriggered_Implementation(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogBoatCore, Log, TEXT("Movement Action Triggered, Value: %s"), *InputActionValue.Get<FVector2d>().ToString());
}


