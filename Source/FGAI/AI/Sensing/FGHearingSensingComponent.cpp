#include "FGHearingSensingComponent.h"
#include "FGAI/FGNoiseActor.h"
#include "FGAI/FGAIGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

UFGHearingSensingComponent::UFGHearingSensingComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGHearingSensingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	auto* GI = Cast<UFGAIGameInstance>(GetWorld()->GetGameInstance());
	TArray<AFGNoiseActor*> NoiseActors = GI->GetNoiseActors();

	const FVector MyLocation = GetOwner()->GetActorLocation();
	const float HearingRangeSq = FMath::Square(HearingRange);
	
	//....Debug....
	UKismetSystemLibrary::DrawDebugSphere(this, MyLocation, HearingRange, 12,
		FLinearColor::Red);
	//....End Debug....
	
	for (auto* Noise : NoiseActors)
	{
		float DistanceToNoiseSq = FVector::DistSquared(MyLocation, Noise->GetActorLocation());
		float NoiseRangeSq = FMath::Square(Noise->StartRadius);

		if (DistanceToNoiseSq < (NoiseRangeSq + HearingRangeSq) && SensedNoiseActors.Contains(Noise) == false)
		{
			Noise->RegisterDetection(this);
			
			FFGHearingSensingResults HearingResults;
			HearingResults.NoiseInstigator = Noise->NoiseInstigator;
			HearingResults.NoiseLocation = Noise->GetActorLocation();
			OnNoiseHeard.Broadcast(HearingResults);
		}
	}
}

void UFGHearingSensingComponent::AddSensedNoiseActor(AFGNoiseActor* NoiseActor)
{
	if (SensedNoiseActors.Contains(NoiseActor) == true)
		return;

	SensedNoiseActors.Add(NoiseActor);
}

void UFGHearingSensingComponent::RemoveSensedNoiseActor(AFGNoiseActor* NoiseActor)
{
	if (SensedNoiseActors.Contains(NoiseActor) == false)
		return;

	SensedNoiseActors.Remove(NoiseActor);
}
