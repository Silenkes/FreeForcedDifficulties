// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_RightShapePlateManager.generated.h"

class ACPP_RightShapePlate;

UCLASS()
class PROJECTDIAMOND_API ACPP_RightShapePlateManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_RightShapePlateManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Sounds")
	USoundBase* SuccessSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variable that contains actors of the RightShapePlate class belonging to the current manager
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default_Plates")
	TArray<ACPP_RightShapePlate*> RightShapePlates;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RegisterPlate(ACPP_RightShapePlate* Plate);
	void CheckCompletedPlates();

private:
	bool IsActorsAlreadyDestroyed;
};
