// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CPP_MovingPlatform.generated.h"

class UCurveFloat;

UCLASS()
class PROJECTDIAMOND_API ACPP_MovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_MovingPlatform();

	UFUNCTION()
	void TimelineMoving(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	// To where actor the platform will move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Moving")
	AActor* FinishActorToMove;

	// If FinishActorToMove are not set, then platform will move to FinishCoordinatesToMove
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Moving")
	FVector FinishCoordinatesToMove;

	UFUNCTION()
	void SuspendPlatformMoving();

	UFUNCTION()
	void ResumePlatformMoving();

	UFUNCTION(BlueprintCallable, Category = "Default_Moving")
	void ChangeMovingSpeed(float NewMovingSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimeline CurveTimeLine;

	UPROPERTY(EditAnywhere, Category = "Default_Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Moving")
	float MovingSpeed = 1.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Start location coordinates form which the platform will start moving
	FVector StartLocation;

	// Finish location coordinates to which the platform will move
	FVector FinishLocation;
};
