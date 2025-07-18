// This game is whole copyright, so be carefull!


#include "CPP_AstralShape.h"
#include "CPP_ShapesManager.h"

// Sets default values
ACPP_AstralShape::ACPP_AstralShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_AstralShape::BeginPlay()
{
	Super::BeginPlay();
	
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_ShapesManager::StaticClass()))
	{
		ACPP_ShapesManager* ShapesManager = Cast<ACPP_ShapesManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_ShapesManager::StaticClass()));
		if (ShapesManager)
		{
			ShapesManager->AstralShapesArray.Add(this);
		}
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ShapesManager not found!"));
}

void ACPP_AstralShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_AstralShape::IncreaseSize()
{
	FVector CurrentScale = GetActorScale3D();

	if (CurrentScale.X < MaxScale.X)
	{
		CurrentScale.X += IncreasingScaleRate.X;
		if (IncreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, IncreasingSound, GetActorLocation());
		}
	}
	
	if (CurrentScale.Y < MaxScale.Y)
	{
		CurrentScale.Y += IncreasingScaleRate.Y;
		if (IncreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, IncreasingSound, GetActorLocation());
		}
	}

	if (CurrentScale.Z < MaxScale.Z)
	{
		CurrentScale.Z += IncreasingScaleRate.Z;
		if (IncreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, IncreasingSound, GetActorLocation());
		}
	}

	SetActorScale3D(CurrentScale);
}

void ACPP_AstralShape::DecreaseSize()
{
	FVector CurrentScale = GetActorScale3D();

	if (CurrentScale.X > MinScale.X)
	{
		CurrentScale.X -= DecreasingScaleRate.X;
		if (DecreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DecreasingSound, GetActorLocation(), 3.f);
		}
	}

	if (CurrentScale.Y > MinScale.Y)
	{
		CurrentScale.Y -= DecreasingScaleRate.Y;
		if (DecreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DecreasingSound, GetActorLocation(), 3.f);
		}
	}

	if (CurrentScale.Z > MinScale.Z)
	{
		CurrentScale.Z -= DecreasingScaleRate.Z;
		if (DecreasingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DecreasingSound, GetActorLocation(), 3.f);
		}
	}

	SetActorScale3D(CurrentScale);
}

// This function is called from ShapesManager, when it needs to move or change the size of nonastral shape
void ACPP_AstralShape::MoveNonAstralShape()
{
	if (ShapeToMove)
	{
		ShapeToMove->SetActorTransform(FTransform(GetActorRotation(), (FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + ZOffset)), GetActorScale3D()));
	}
}
