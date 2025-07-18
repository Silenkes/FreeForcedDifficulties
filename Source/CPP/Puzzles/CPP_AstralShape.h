// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CPPI_ShapeScaleChanging.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_AstralShape.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_AstralShape : public AActor, public ICPPI_ShapeScaleChanging
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_AstralShape();

	// Another static shape, that will be moved in nonastral world, after this shape was moved
	UPROPERTY(EditAnywhere, Category = "Default_Moving")
	AActor* ShapeToMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_ScaleChanging")
	FVector IncreasingScaleRate = FVector(0.0f, 0.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_ScaleChanging")
	FVector DecreasingScaleRate = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Default_Sounds")
	USoundBase* IncreasingSound;

	UPROPERTY(EditAnywhere, Category = "Default_Sounds")
	USoundBase* DecreasingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_ScaleChanging")
	FVector MaxScale = GetActorScale3D();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_ScaleChanging")
	FVector MinScale = GetActorScale3D();

	// Offset between two worlds (astral and nonastral) relative to Z coordinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default_Offset")
	float ZOffset = 250859.090825;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void IncreaseSize() override;
	virtual void DecreaseSize() override;
	void MoveNonAstralShape();
};
