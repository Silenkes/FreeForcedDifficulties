// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_M314.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_M314 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_M314();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData, meta = (ExposeOnSpawn = "true"))
	float StartDamage = 35.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponData, meta = (ExposeOnSpawn = "true"))
	bool bIsInfiniteAmmo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter for SavedAmmoCount variable
	UFUNCTION(BlueprintCallable, Category = WeaponData)
	int GetSavedAmmoCount() const { return SavedAmmoCount; }

	// Setter for SavedAmmoCount variable
	UFUNCTION(BlueprintCallable, Category = WeaponData)
	void SetSavedAmmoCount(int NewAmmoCount) { SavedAmmoCount = NewAmmoCount; }

	UFUNCTION(BlueprintCallable, Category = WeaponData)
	int GetSavedMaxAmmoCount() const { return SavedMaxAmmoCount; }

	UFUNCTION(BlueprintCallable, Category = WeaponData)
	void SetSavedMaxAmmoCount(int NewMaxAmmoCount) { SavedMaxAmmoCount = NewMaxAmmoCount; }

private:
	/** Variable for saving ammunition count after dropping the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponData, meta = (AllowPrivateAccess = "true"))
	int SavedAmmoCount = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponData, meta = (AllowPrivateAccess = "true"))
	int SavedMaxAmmoCount = -1;
};