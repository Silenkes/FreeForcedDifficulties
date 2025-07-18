// This game is whole copyright, so be carefull!


#include "CPP_StopMovingPlatformPlate.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_MovingPlatform.h"

// Sets default values
ACPP_StopMovingPlatformPlate::ACPP_StopMovingPlatformPlate()
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
void ACPP_StopMovingPlatformPlate::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxCollision)
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_StopMovingPlatformPlate::OnBoxCollisionBeginOverlap);
}

void ACPP_StopMovingPlatformPlate::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPlatePressed)
	{
		IsPlatePressed = true;
		if (PlateMesh)
		{
			FVector NewLocation = PlateMesh->GetComponentLocation();
			NewLocation.Z -= 4.f;
			PlateMesh->SetWorldLocation(NewLocation);

			if (PlatePressSound)
				UGameplayStatics::PlaySoundAtLocation(this, PlatePressSound, GetActorLocation());

			SuspendMovingPlatforms();
		}
	}
}

void ACPP_StopMovingPlatformPlate::SuspendMovingPlatforms()
{
	for (ACPP_MovingPlatform* Platforms : PlatformsToSuspend)
	{
		if (Platforms)
			Platforms->SuspendPlatformMoving();
	}

	GetWorldTimerManager().SetTimer(
		ResumeMovingPlatformsTimerHandle,
		this,
		&ACPP_StopMovingPlatformPlate::ResumeMovingPlatforms,
		SuspendPlatformsDuration,
		false
	);
}

void ACPP_StopMovingPlatformPlate::ResumeMovingPlatforms()
{
	for (ACPP_MovingPlatform* Platforms : PlatformsToSuspend)
	{
		if (Platforms)
			Platforms->ResumePlatformMoving();
	}

	IsPlatePressed = false;
	FVector NewLocation = PlateMesh->GetComponentLocation();
	NewLocation.Z += 4.f;
	PlateMesh->SetWorldLocation(NewLocation);

	if (PlateReleaseSound)
		UGameplayStatics::PlaySoundAtLocation(this, PlateReleaseSound, GetActorLocation());
}

// Called every frame
void ACPP_StopMovingPlatformPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

