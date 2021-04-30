#include "FGTargetingComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

void UFGTargetingComponent::BeginPlay()
{
	VisionSense = Cast<UFGVisionSensingComponent>(GetOwner()->GetComponentByClass(UFGVisionSensingComponent::StaticClass()));
	if (VisionSense != nullptr)
	{
		VisionSense->OnTargetSensed.AddDynamic(this, &UFGTargetingComponent::Handle_VisionSense);
		VisionSense->OnTargetLost.AddDynamic(this, &UFGTargetingComponent::Handle_VisionLost);
	}

	DamageSense = Cast<UDamageSenseComponent>(GetOwner()->GetComponentByClass(UDamageSenseComponent::StaticClass()));
	if (DamageSense != nullptr)
	{
		DamageSense->OnDamageSensed.AddDynamic(this, &UFGTargetingComponent::Handle_DamageSense);
	}

	HearingSense = Cast<UFGHearingSensingComponent>(GetOwner()->GetComponentByClass(UFGHearingSensingComponent::StaticClass()));
	if (HearingSense != nullptr)
	{
		HearingSense->OnNoiseHeard.AddDynamic(this, &UFGTargetingComponent::Handle_HearingSense);
	}
}

void UFGTargetingComponent::Handle_VisionSense(const FFGVisionSensingResults& VisionSenseInfo)
{
	CurrentTarget = VisionSenseInfo.SensedActor;
}

void UFGTargetingComponent::Handle_VisionLost(const FFGVisionSensingResults& VisionSenseInfo)
{
	CurrentTarget = nullptr;
}

void UFGTargetingComponent::Handle_DamageSense(const FFGDamageSenseInfo& DamageSenseInfo)
{
	
}

void UFGTargetingComponent::Handle_HearingSense(const FFGHearingSensingResults& HearingSenseInfo)
{
	LatestHeardNoise = HearingSenseInfo;
	bHeardNoise = true;
}
