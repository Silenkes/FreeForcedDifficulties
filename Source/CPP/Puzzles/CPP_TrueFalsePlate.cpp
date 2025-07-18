// This game is whole copyright, so be carefull!


#include "CPP_TrueFalsePlate.h"
#include "ProjectDiamond/ProjectDiamondCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_TrueFalsePlate::ACPP_TrueFalsePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(SceneRoot);
	PlateMesh->SetMobility(EComponentMobility::Static);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ACPP_TrueFalsePlate::BeginPlay()
{
	Super::BeginPlay();
	if (BoxCollision)
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_TrueFalsePlate::OnBoxCollisionBeginOverlap);
}

void ACPP_TrueFalsePlate::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectDiamondCharacter>(OtherActor))
	{
		if (!IsPlateTrue)
		{
			if (TeleportationTarget)
				OtherActor->SetActorLocation(TeleportationTarget->GetActorLocation());

			else
				OtherActor->SetActorLocation(TeleportationCoordinate);

			if (FailureSound)
				UGameplayStatics::PlaySound2D(this, FailureSound, 0.4f);
		}
	}
}

// Called every frame
void ACPP_TrueFalsePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

