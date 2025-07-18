// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_TrueNumberPlate.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_TrueNumberPlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TrueNumberPlate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* TXT_Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Materials")
	UMaterialInstance* SuccessMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Materials")
	UMaterialInstance* FailureMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Sounds")
	USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Sounds")
	USoundBase* FailureSound;

	//* Actor that will be moved if the answer (TXT_Number) is correct (equal to the TrueNumber)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_ActorToMove")
	AActor* ActorToMove;

	//* Right number that must be displayed on the TXT_Number when player steps on the plate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Numbers")
	int32 TrueNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Numbers")
	float LiftStrength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Numbers")
	float NumberChangeInterval = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Numbers")
	TArray<int32> PossibleDisplayableNumbers;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ChangeNumber();

	UFUNCTION()
	void ResumeTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool PlayerSucceed = false;
	FTimerHandle NumberChangeTimerHandle;
	FTimerHandle ResumeTimerHandle;
	UMaterialInterface* DefaultMaterial;
	int32 RandomIndex;
	int32 RandomNumber;
};
