// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectDiamond/ProjectDiamondCharacter.h"
#include "Interfaces/CPPI_ShapeScaleChanging.h"
#include "CPP_DecreasingWeaponComponent.generated.h"

UCLASS()
class PROJECTDIAMOND_API UCPP_DecreasingWeaponComponent : public USkeletalMeshComponent, public ICPPI_WeaponHandler
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem* FireParticle;
	
	// The Actor class from which the current skeletal mesh was attached to character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parent)
	TSubclassOf<AActor> ParentActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float LineTraceDistance = 2000.0f;

protected:
	virtual void BeginPlay() override;
	void LineTraceByChannel();

	//* Make the weapon Fire and decreases the size of the shapes hit by the weapon;
	virtual void Fire() override;

	virtual void DropWeapon() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	AProjectDiamondCharacter* OwnerCharacter;
};
