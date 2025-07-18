// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CPP_TrueFalsePlate.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_TrueFalsePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TrueFalsePlate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollision;

	// if player chosed the wrong plate, then he will be teleported to the TeleportationTarget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	AActor* TeleportationTarget;

	// for more exact coordinates of the teleportation target (ATTENTION: Only if TeleportationTarget is not set!)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	FVector TeleportationCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Gameplay")
	bool IsPlateTrue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Sounds")
	USoundBase* FailureSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
