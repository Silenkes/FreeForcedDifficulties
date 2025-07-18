// This game is whole copyright, so be carefull!


#include "CPP_Teleport.h"
#include "CPP_ShapesManager.h"
#include "Engine/SkyLight.h"
#include "Components/VolumetricCloudComponent.h"
#include "Components/SkyLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/GameplayStatics.h"

ACPP_Teleport::ACPP_Teleport()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACPP_Teleport::ChangeSkyLightColor(FColor NewColor)
{
	ASkyLight* SkyLight = Cast<ASkyLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ASkyLight::StaticClass()));

	if (SkyLight)
	{
		SkyLight->GetLightComponent()->SetLightColor(NewColor);
	}
}

void ACPP_Teleport::ChangeDirectionalLightColor(FColor NewColor)
{
	ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));
	
	if (DirectionalLight)
	{
		DirectionalLight->SetLightColor(NewColor);
	}
}

void ACPP_Teleport::ChangeShapesTransform()
{
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_ShapesManager::StaticClass()))
	{
		ACPP_ShapesManager* ShapesManager = Cast<ACPP_ShapesManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_ShapesManager::StaticClass()));
		if (ShapesManager)
		{
			ShapesManager->SynchronizeShapes();
		}
	}
}

void ACPP_Teleport::ChangeCloudsVisibility(bool NewVisibility)
{
	AVolumetricCloud* Clouds = Cast<AVolumetricCloud>(UGameplayStatics::GetActorOfClass(GetWorld(), AVolumetricCloud::StaticClass()));

	if (Clouds)
	{
		UVolumetricCloudComponent* CloudsComponent = Clouds->GetComponentByClass<UVolumetricCloudComponent>();

		if (CloudsComponent)
			CloudsComponent->SetVisibility(NewVisibility);
	}
}

void ACPP_Teleport::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision = FindComponentByTag<UBoxComponent>(FName("BoxCol"));

	if (BoxCollision)
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Teleport::OnBoxCollisionBeginOverlap);
}

void ACPP_Teleport::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectDiamondCharacter* PlayerCharacter = Cast<AProjectDiamondCharacter>(OtherActor);
	if (PlayerCharacter)
		if (TeleportationTarget)
		{
			OtherActor->SetActorTransform(FTransform(TeleportationTarget->GetActorTransform()));

			if (PlayerCharacter->GetController())
				PlayerCharacter->GetController()->SetControlRotation(TeleportationTarget->GetActorRotation());

			if (TeleportationSound)
			{
				UGameplayStatics::PlaySound2D(this, TeleportationSound);
			}

			ChangeShapesTransform();

			if (IsPortalToAstral)
			{
				ChangeSkyLightColor(FColor(0, 109, 83));
				ChangeDirectionalLightColor(FColor(0, 109, 83));
				ChangeCloudsVisibility(false);
			}
			
			if (IsPortalToRealWorld)
			{
				ChangeSkyLightColor(FColor(255, 255, 255));
				ChangeDirectionalLightColor(FColor(255, 255, 255));
				ChangeCloudsVisibility(true);
			}
		}
}

void ACPP_Teleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}