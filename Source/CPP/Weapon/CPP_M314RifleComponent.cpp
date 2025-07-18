// This game is whole copyright, so be carefull!


#include "CPP_M314RifleComponent.h"
#include "CPP_M314.h"


void UCPP_M314RifleComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<AProjectDiamondCharacter>(GetOwner());
	if(OwnerCharacter)
		OwnerCharacter->SetCurrentWeapon(this);
}

void UCPP_M314RifleComponent::DropWeapon()
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
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ParentActorClass, SpawnLocation, SpawnRotation);
	ACPP_M314* ParentActor = Cast<ACPP_M314>(SpawnedActor);
	
	if (ParentActor)
	{
		// Transferring the ammo count from the current weapon component to the spawned parent actor for saving the ammo count
		ParentActor->SetSavedAmmoCount(CurrentAmmo);
		ParentActor->SetSavedMaxAmmoCount(MaxAmmo);
		ParentActor->StartDamage = StartDamage;
		ParentActor->bIsInfiniteAmmo = bIsInfiniteAmmo;
	}

	SpawnedActor = nullptr;
	ParentActor = nullptr;

	// Destroying the current skeletal mesh component
	DestroyComponent();
}
