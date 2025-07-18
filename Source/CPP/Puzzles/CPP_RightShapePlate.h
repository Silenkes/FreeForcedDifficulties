// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CPP_RightShapePlate.generated.h"

class ACPP_RightShapePlateManager;

UCLASS()
class PROJECTDIAMOND_API ACPP_RightShapePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_RightShapePlate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Sounds")
	USoundBase* PlatePressSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Sounds")
	USoundBase* PlateReleaseSound;

	// The actor that should be placed on the plate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	AActor* RightShapeActor;

	// * Actor that will be destroyed if player moved right shape on the plate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	AActor* ActorToDestroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	ACPP_RightShapePlateManager* RightShapePlateManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsPlateCompleted() const { return PlateCompleted; }
	void KillActorToDestroy();

private:
	// * Variable that contains number of objects that were placed on the plate
	int32 ObjectsOnPlate = 0;
	bool RightShapeOnPlate = false;
	
	// * Checks if the all of requirements to destroy the ActorToDestroy are met
	bool PlateCompleted = false;
};
