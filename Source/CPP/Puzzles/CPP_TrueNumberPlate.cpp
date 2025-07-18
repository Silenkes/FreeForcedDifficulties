// This game is whole copyright, so be carefull!


#include "CPP_TrueNumberPlate.h"
#include "ProjectDiamond/ProjectDiamondCharacter.h"

// Sets default values
ACPP_TrueNumberPlate::ACPP_TrueNumberPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	PlateMesh->SetupAttachment(SceneRoot);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneRoot);
	TXT_Number = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TXT_Number"));
	TXT_Number->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ACPP_TrueNumberPlate::BeginPlay()
{
	Super::BeginPlay();

	if (PlateMesh)
		DefaultMaterial = PlateMesh->GetMaterial(0);

	GetWorldTimerManager().SetTimer(
		NumberChangeTimerHandle,
		this,
		&ACPP_TrueNumberPlate::ChangeNumber,
		NumberChangeInterval,
		true
	);

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_TrueNumberPlate::OnBoxCollisionBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACPP_TrueNumberPlate::OnBoxCollisionEndOverlap);
	}
}

void ACPP_TrueNumberPlate::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectDiamondCharacter* PlayerCharacter = Cast<AProjectDiamondCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		if (PlateMesh)
		{
			PlateMesh->SetWorldLocation(FVector(PlateMesh->GetComponentLocation().X, PlateMesh->GetComponentLocation().Y, PlateMesh->GetComponentLocation().Z - 4));
		}

		if (PlayerSucceed)
			return;

		if (RandomNumber == TrueNumber)
		{
			PlayerSucceed = true;
				
			if (GetWorldTimerManager().IsTimerActive(NumberChangeTimerHandle))
			{
				GetWorldTimerManager().ClearTimer(NumberChangeTimerHandle);
				NumberChangeTimerHandle.Invalidate();
			}

			if (SuccessSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SuccessSound, GetActorLocation());
			}

			if (SuccessMaterial)
			{
				PlateMesh->SetMaterial(0, SuccessMaterial);
			}

			if (ActorToMove)
			{
				FVector NewLocation = ActorToMove->GetActorLocation();
				NewLocation.Z += LiftStrength;
				ActorToMove->SetActorLocation(NewLocation);
			}
		}

		else
		{
			if (GetWorldTimerManager().IsTimerActive(NumberChangeTimerHandle))
			{
				GetWorldTimerManager().PauseTimer(NumberChangeTimerHandle);
				GetWorldTimerManager().SetTimer(
					ResumeTimerHandle,
					this,
					&ACPP_TrueNumberPlate::ResumeTimer,
					3.f,
					false
				);

				if (FailureSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FailureSound, GetActorLocation());
				}

				if (FailureMaterial)
				{
					PlateMesh->SetMaterial(0, FailureMaterial);
				}
			}
		}
	}
}

void ACPP_TrueNumberPlate::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AProjectDiamondCharacter* PlayerCharacter = Cast<AProjectDiamondCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		if (PlateMesh)
		{
			PlateMesh->SetWorldLocation(FVector(PlateMesh->GetComponentLocation().X, PlateMesh->GetComponentLocation().Y, PlateMesh->GetComponentLocation().Z + 4));
		}
	}
}

void ACPP_TrueNumberPlate::ChangeNumber()
{
	if (PossibleDisplayableNumbers.Num() > 0)
	{
		RandomIndex = FMath::RandRange(0, PossibleDisplayableNumbers.Num() - 1);
		RandomNumber = PossibleDisplayableNumbers[RandomIndex];
		TXT_Number->SetText(FText::AsNumber(RandomNumber));
	}

	else
	{
		if (GetWorldTimerManager().IsTimerActive(NumberChangeTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(NumberChangeTimerHandle);
			NumberChangeTimerHandle.Invalidate();
		}
	}
}

void ACPP_TrueNumberPlate::ResumeTimer()
{
	GetWorldTimerManager().UnPauseTimer(NumberChangeTimerHandle);
	PlateMesh->SetMaterial(0, DefaultMaterial);
}

// Called every frame
void ACPP_TrueNumberPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}