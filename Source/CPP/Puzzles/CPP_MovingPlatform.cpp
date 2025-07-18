// This game is whole copyright, so be carefull!


#include "CPP_MovingPlatform.h"

// Sets default values
ACPP_MovingPlatform::ACPP_MovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(SceneRoot);
}

void ACPP_MovingPlatform::TimelineMoving(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, FinishLocation, Value);
	SetActorLocation(NewLocation);
}

// Called when the game starts or when spawned
void ACPP_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	if (FinishActorToMove)
		FinishLocation = FinishActorToMove->GetActorLocation();

	else
		FinishLocation = FinishCoordinatesToMove;

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineMoving"));
		CurveTimeLine.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeLine.SetPlayRate(MovingSpeed);
		CurveTimeLine.SetLooping(true);
		CurveTimeLine.PlayFromStart();
	}
}

void ACPP_MovingPlatform::SuspendPlatformMoving()
{
	if (CurveTimeLine.IsPlaying())
		CurveTimeLine.Stop();
}

void ACPP_MovingPlatform::ResumePlatformMoving()
{
	CurveTimeLine.Play();
}

void ACPP_MovingPlatform::ChangeMovingSpeed(float NewMovingSpeed)
{
	MovingSpeed = NewMovingSpeed;
	CurveTimeLine.SetPlayRate(MovingSpeed);
}

// Called every frame
void ACPP_MovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeLine.TickTimeline(DeltaTime);
}