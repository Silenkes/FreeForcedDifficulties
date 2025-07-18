// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectDiamondCharacter.h"
#include "ProjectDiamondProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectDiamondCharacter

AProjectDiamondCharacter::AProjectDiamondCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AProjectDiamondCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	BaseMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);

			UEnhancedInputUserSettings* UserSettings = Subsystem->GetUserSettings();
			if (!(UserSettings->IsMappingContextRegistered(DefaultMappingContext)))
			{
				UserSettings->RegisterInputMappingContext(DefaultMappingContext);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AProjectDiamondCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectDiamondCharacter::Move);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AProjectDiamondCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AProjectDiamondCharacter::Sprint);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectDiamondCharacter::Look);

		// Drop current weapon
		EnhancedInputComponent->BindAction(DropCurrentWeaponAction, ETriggerEvent::Started, this, &AProjectDiamondCharacter::DropCurrentWeapon);

		// Attack someone or something
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProjectDiamondCharacter::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AProjectDiamondCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AProjectDiamondCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * MouseSensitivityMultiplier);
		AddControllerPitchInput(LookAxisVector.Y * MouseSensitivityMultiplier);
	}
}

void AProjectDiamondCharacter::DropCurrentWeapon()
{
	if (bHasRifle && Controller != nullptr && CurrentWeapon != nullptr)
	{
		auto WeaponHandlerInterface = Cast<ICPPI_WeaponHandler>(CurrentWeapon);

		if (WeaponHandlerInterface)
		{
			WeaponHandlerInterface->DropWeapon();
			bHasRifle = false;
			CurrentWeapon = nullptr;
		}
	}
}

void AProjectDiamondCharacter::Attack()
{
	if (bHasRifle && Controller != nullptr && CurrentWeapon != nullptr)
	{
		auto WeaponHandlerInterface = Cast<ICPPI_WeaponHandler>(CurrentWeapon);

		if (WeaponHandlerInterface)
		{
			WeaponHandlerInterface->Fire();
		}
	}
}

void AProjectDiamondCharacter::Sprint(const FInputActionValue& Value)
{
	// input is a bool
	bool bIsSprinting = Value.Get<bool>();

	if (Controller != nullptr)
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			if (bIsSprinting)
			{
				CurrentSpeed = FMath::FInterpTo(CurrentSpeed, BaseMaxWalkSpeed + 401.5f, GetWorld()->GetDeltaSeconds(), 3.0f);
				MoveComp->MaxWalkSpeed = CurrentSpeed;
			}

			else
			{
				MoveComp->MaxWalkSpeed = BaseMaxWalkSpeed;
				CurrentSpeed = BaseMaxWalkSpeed;
			}
		}
	}
}

void AProjectDiamondCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AProjectDiamondCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AProjectDiamondCharacter::SetCurrentWeapon(USkeletalMeshComponent* NewWeapon)
{
	CurrentWeapon = NewWeapon;
}

void AProjectDiamondCharacter::ChangeMouseSensitivity(float NewSensitivity)
{
	MouseSensitivityMultiplier = NewSensitivity;
}

void AProjectDiamondCharacter::SetMaxWalkSpeed(float NewMaxWalkSpeed)
{
	BaseMaxWalkSpeed = NewMaxWalkSpeed;
	CurrentSpeed = NewMaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}
