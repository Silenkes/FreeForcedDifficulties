// This game is whole copyright, so be carefull!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_AstralShape.h"
#include "CPP_ShapesManager.generated.h"

UCLASS()
class PROJECTDIAMOND_API ACPP_ShapesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_ShapesManager();
	TArray<ACPP_AstralShape*> AstralShapesArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SynchronizeShapes(); // Sets the position and scale of astral shapes to the position and scale of nonastral shapes
};
