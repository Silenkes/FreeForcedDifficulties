// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectDiamond/ProjectDiamondCharacter.h"
#include "CPP_M314RifleComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDIAMOND_API UCPP_M314RifleComponent : public USkeletalMeshComponent, public ICPPI_WeaponHandler
{
	GENERATED_BODY()
public:
	// The Actor class from which the current skeletal mesh was attached to character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parent)
	TSubclassOf<AActor> ParentActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData)
	int MaxAmmo = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData)
	int CurrentAmmo = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData, meta = (ExposeOnSpawn = "true"))
	float StartDamage = 35.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData, meta = (ExposeOnSpawn = "true"))
	bool bIsInfiniteAmmo;

protected:
	virtual void BeginPlay() override;
	virtual void DropWeapon() override;

private:
	AProjectDiamondCharacter* OwnerCharacter;
};
