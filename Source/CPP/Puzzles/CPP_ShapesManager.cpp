// This game is whole copyright, so be carefull!


#include "CPP_ShapesManager.h"

// Sets default values
ACPP_ShapesManager::ACPP_ShapesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_ShapesManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_ShapesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_ShapesManager::SynchronizeShapes()
{
	if (AstralShapesArray.Num() > 0)
	{
		for (ACPP_AstralShape* AstralShape : AstralShapesArray)
		{
			if (AstralShape)
			{
				AstralShape->MoveNonAstralShape();
			}
		}
	}
}

