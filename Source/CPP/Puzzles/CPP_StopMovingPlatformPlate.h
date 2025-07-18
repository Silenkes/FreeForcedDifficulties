// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CPP_StopMovingPlatformPlate.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_StopMovingPlatformPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_StopMovingPlatformPlate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Sounds")
	USoundBase* PlatePressSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Sounds")
	USoundBase* PlateReleaseSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SuspendMovingPlatforms();

	UFUNCTION()
	void ResumeMovingPlatforms();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Platforms")
	float SuspendPlatformsDuration = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Platforms")
	TArray<ACPP_MovingPlatform*> PlatformsToSuspend;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool IsPlatePressed = false;
	FTimerHandle ResumeMovingPlatformsTimerHandle;
};
