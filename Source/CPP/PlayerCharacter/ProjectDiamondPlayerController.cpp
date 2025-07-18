// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectDiamondPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AProjectDiamondPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get Enhanced Input Subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
