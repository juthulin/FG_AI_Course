#include "FGAIStateSuspicious.h"
#include "AIController.h"
#include "FGAI/Components/FGTargetingComponent.h"

void UFGAIStateSuspicious::Setup()
{
	StateName = TEXT("Suspicious");
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	Controller = Cast<AAIController>(OwnerPawn->Controller);

	TargetingComp = Cast<UFGTargetingComponent>(GetOwner()->GetComponentByClass(UFGTargetingComponent::StaticClass()));

	Super::Setup();
}

void UFGAIStateSuspicious::OnActivated()
{
	RemainingWaitTime = TimeToWait;
	FirstNoiseLocation = TargetingComp->LatestHeardNoise.NoiseLocation;
	Controller->MoveToLocation(FirstNoiseLocation);
	
	Super::OnActivated();
}

void UFGAIStateSuspicious::OnDeactivated()
{

	Super::OnDeactivated();
}

FName UFGAIStateSuspicious::TickActive(float DeltaTime)
{
	if (TargetingComp != nullptr)
	{
		if (TargetingComp->CurrentTarget != nullptr)
		{
			ChangeState(TEXT("Attacking"));
			return Super::TickActive(DeltaTime);
		}
	
		RotateTowardsTarget(FirstNoiseLocation);
		const FVector DistanceToNoise = FirstNoiseLocation - GetOwner()->GetActorLocation();
		if (DistanceToNoise.IsNearlyZero(150.f))
		{
			RemainingWaitTime -= DeltaTime;

			if (RemainingWaitTime <= 0.f)
			{
				TargetingComp->bHeardNoise = false;
				ChangeState(TEXT("Idle"));
			}
		}
	}
	
	return Super::TickActive(DeltaTime);
}
