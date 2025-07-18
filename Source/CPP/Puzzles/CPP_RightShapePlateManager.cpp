// This game is whole copyright, so be carefull!


#include "CPP_RightShapePlateManager.h"
#include "CPP_RightShapePlate.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_RightShapePlateManager::ACPP_RightShapePlateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACPP_RightShapePlateManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_RightShapePlateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_RightShapePlateManager::RegisterPlate(ACPP_RightShapePlate* Plate)
{
	if (Plate)
		RightShapePlates.Add(Plate);
}

void ACPP_RightShapePlateManager::CheckCompletedPlates()
{
	// Checks if manager already destroyed all ActorToDestroy in all plates before;
	if (IsActorsAlreadyDestroyed)
		return;

	// * If at least one plate is not completed, return
	for (ACPP_RightShapePlate* Plate : RightShapePlates)
	{
		if (!Plate || !Plate->IsPlateCompleted())
			return;
	}

	// * If all plates are completed, destroy all ActorToDestroy in all of this plates
	for (ACPP_RightShapePlate* Plate : RightShapePlates)
	{
		if (Plate)
			Plate->KillActorToDestroy();
	}

	IsActorsAlreadyDestroyed = true;

	if (SuccessSound)
		UGameplayStatics::PlaySound2D(this, SuccessSound, 1.f);
}

