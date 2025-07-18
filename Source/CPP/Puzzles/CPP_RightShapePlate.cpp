// This game is whole copyright, so be carefull!


#include "CPP_RightShapePlate.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_RightShapePlateManager.h"

// Sets default values
ACPP_RightShapePlate::ACPP_RightShapePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(SceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ACPP_RightShapePlate::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_RightShapePlate::OnBoxCollisionBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACPP_RightShapePlate::OnBoxCollisionEndOverlap);
	}

	if (RightShapePlateManager)
		RightShapePlateManager->RegisterPlate(this);
}

void ACPP_RightShapePlate::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ObjectsOnPlate == 0)
	{
		if (PlatePressSound)
			UGameplayStatics::PlaySoundAtLocation(this, PlatePressSound, GetActorLocation());

		if (PlateMesh)
			PlateMesh->SetWorldLocation(FVector(PlateMesh->GetComponentLocation().X, PlateMesh->GetComponentLocation().Y, PlateMesh->GetComponentLocation().Z - 4));
	}

	if (OtherActor == RightShapeActor)
	{
		RightShapeOnPlate = true;
		ObjectsOnPlate++;
	}

	else
		ObjectsOnPlate++;

	if (ObjectsOnPlate == 1 && RightShapeOnPlate)
	{
		PlateCompleted = true;

		if(RightShapePlateManager)
			RightShapePlateManager->CheckCompletedPlates();
	}

	else
		PlateCompleted = false;
}

void ACPP_RightShapePlate::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ObjectsOnPlate == 1)
	{
		if (PlateReleaseSound)
			UGameplayStatics::PlaySoundAtLocation(this, PlateReleaseSound, GetActorLocation());

		if (PlateMesh)
			PlateMesh->SetWorldLocation(FVector(PlateMesh->GetComponentLocation().X, PlateMesh->GetComponentLocation().Y, PlateMesh->GetComponentLocation().Z + 4));
	}

	if (OtherActor == RightShapeActor)
	{
		RightShapeOnPlate = false;
		ObjectsOnPlate--;
	}

	else
		ObjectsOnPlate--;

	if (ObjectsOnPlate == 1 && RightShapeOnPlate)
	{
		PlateCompleted = true;

		if (RightShapePlateManager)
			RightShapePlateManager->CheckCompletedPlates();
	}

	else
		PlateCompleted = false;
}

// Called every frame
void ACPP_RightShapePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_RightShapePlate::KillActorToDestroy()
{
	if (ActorToDestroy)
		ActorToDestroy->Destroy();
}

