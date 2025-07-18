// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectDiamond/ProjectDiamondCharacter.h"
#include "Components/BoxComponent.h"
#include "CPP_Teleport.generated.h"


UCLASS()
class PROJECTDIAMOND_API ACPP_Teleport : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Teleport();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	AActor* TeleportationTarget;

	UPROPERTY(EditAnywhere, Category = "Default")
	USoundBase* TeleportationSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool IsPortalToAstral = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool IsPortalToRealWorld = false;

	//* Changes the color of the sky light in the level
	UFUNCTION(BlueprintCallable, Category = "Changing")
	void ChangeSkyLightColor(FColor NewColor);

	//* Changes the color of the directional light in the level
	UFUNCTION(BlueprintCallable, Category = "Changing")
	void ChangeDirectionalLightColor(FColor NewColor);

	//* Changes location, rotation and scale of the shapes in the level
	UFUNCTION(BlueprintCallable, Category = "Changing")
	void ChangeShapesTransform();

	UFUNCTION(BlueprintCallable, Category = "Changing")
	void ChangeCloudsVisibility(bool NewVisibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UBoxComponent* BoxCollision;
};
