// This game is whole copyright, so be carefull!


#include "CPP_DecreasingWeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/CollisionProfile.h"
#include "InputMappingContext.h"

void UCPP_DecreasingWeaponComponent::Fire()
{
	if (OwnerCharacter == nullptr)
		return;

	LineTraceByChannel();
}

void UCPP_DecreasingWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<AProjectDiamondCharacter>(GetOwner());

	if (OwnerCharacter)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		AttachToComponent(OwnerCharacter->GetMesh1P(), AttachmentRules, FName(TEXT("DecreasingWeaponGripPoint")));
		OwnerCharacter->SetCurrentWeapon(this);
		UGameplayStatics::PlaySound2D(this, PickupSound);
	}

	if (APlayerController* OwnerController = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		// Set up action bindings
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OwnerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);

			UEnhancedInputUserSettings* UserSettings = Subsystem->GetUserSettings();
			if (!(UserSettings->IsMappingContextRegistered(FireMappingContext)))
			{
				UserSettings->RegisterInputMappingContext(FireMappingContext);
			}
		}
	}
}

void UCPP_DecreasingWeaponComponent::LineTraceByChannel()
{
	APlayerController* OwnerController = Cast<APlayerController>(OwnerCharacter->GetController());

	if (!GetWorld() || !OwnerController)
		return;

	APlayerCameraManager* CameraManager = OwnerController->PlayerCameraManager;

	if (!CameraManager)
		return;

	// Parameters for line tracing
	FVector Start = CameraManager->GetCameraLocation(); // Start position for line tracing;
	FVector ForwardVector = CameraManager->GetCameraRotation().Vector();
	FVector End = ForwardVector * LineTraceDistance + Start; // End position for line tracing;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	// Objects to ignore
	CollisionParams.AddIgnoredActor(OwnerCharacter);
	CollisionParams.AddIgnoredComponent(this);

	// Perform the line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		CollisionParams
	);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 1.0f);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, HitResult.GetActor()->GetName());

		auto ShapeScaleChangingInterface = Cast<ICPPI_ShapeScaleChanging>(HitResult.GetActor());
		if (ShapeScaleChangingInterface)
		{
			ShapeScaleChangingInterface->DecreaseSize();
		}
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetSocketLocation("Muzzle"));
	}

	if (FireAnimation)
	{
		UAnimInstance* AnimInstance = OwnerCharacter->GetMesh1P()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	if (FireParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, FTransform(GetSocketRotation("Muzzle"), GetSocketLocation("Muzzle"), FVector(0.15f, 0.15f, 0.15f)), true);
	}
}

void UCPP_DecreasingWeaponComponent::DropWeapon()
{
	if (!OwnerCharacter || !ParentActorClass || !GetWorld())
		return;

	/** Location parameter for spawning the actor from wich current skeletal mesh component was attached to character */
	FVector SpawnLocation;

	/** Rotation parameter for spawning the actor from wich current skeletal mesh component was attached to character */
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// Check the space in front of the character to make sure the weapon will not be spawned inside a wall or smth else and change the spawn location if needed

	FVector CheckStart = OwnerCharacter->GetActorLocation();
	FVector CheckEnd = CheckStart + OwnerCharacter->GetActorForwardVector() * 125.0f;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(OwnerCharacter);
	CollisionParams.AddIgnoredComponent(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		CheckStart,
		CheckEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(30.f, 65.f),
		CollisionParams
	);

	if (bHit)
	{
		SpawnLocation = HitResult.Location - OwnerCharacter->GetActorForwardVector() * 20.0f;
	}
	else
	{
		SpawnLocation = CheckEnd;
	}

	// Spawning the actor from which current skeletal mesh component was attached to character
	GetWorld()->SpawnActor<AActor>(ParentActorClass, SpawnLocation, SpawnRotation);

	// Destroying the current skeletal mesh component
	DestroyComponent();
}

void UCPP_DecreasingWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!OwnerCharacter)
		return;

	if (APlayerController* OwnerController = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OwnerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}

	Super::EndPlay(EndPlayReason);
}
