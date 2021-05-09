#include "FGAIStateAttacking.h"
#include "AIController.h"
#include "FGAI/Components/FGTargetingComponent.h"
#include "FGAI/Components/HealthComponent.h"

void UFGAIStateAttacking::Setup()
{
	StateName = InStateName;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	Controller = Cast<AAIController>(OwnerPawn->Controller);

	TargetingComp = Cast<UFGTargetingComponent>(GetOwner()->GetComponentByClass(UFGTargetingComponent::StaticClass()));

	Super::Setup();
}

void UFGAIStateAttacking::OnActivated()
{
	if (TargetingComp != nullptr)
		bHasTarget = TargetingComp->CurrentTarget != nullptr;
	else
		bHasTarget = false;
	
	UpdateTargetLocation();

	Super::OnActivated();
}

void UFGAIStateAttacking::OnDeactivated()
{
	Super::OnDeactivated();
}

FName UFGAIStateAttacking::TickActive(float DeltaTime)
{
	if (TargetingComp != nullptr)
		bHasTarget = TargetingComp->CurrentTarget != nullptr;
	else
		bHasTarget = false;
	
	UpdateTimer -= DeltaTime;
	if (UpdateTimer <= 0.f)
	{
		UpdateTargetLocation();
		UpdateTimer = TimeBetweenUpdates;
	}

	WaitTimer -= DeltaTime;
	if (bHasTarget)
	{
		RotateTowardsTarget(TargetingComp->CurrentTarget->GetActorLocation());
		
		if (bIsAttacking)
		{
			if (WaitTimer <= 0.f)
			{
				auto* Health = Cast<UHealthComponent>(TargetingComp->CurrentTarget->GetComponentByClass(UHealthComponent::StaticClass()));
				if (Health != nullptr)
				{
					Health->Health -= 10.f;
				}
				WaitTimer = WaitAfterAttackMax;
			}
		}
		else
		{
			const FVector DistanceToTarget = TargetLocation - GetOwner()->GetActorLocation();
			if (DistanceToTarget.IsNearlyZero(150.f))
			{
				bIsAttacking = true;
				WaitTimer = WaitAfterMoveMax;
			}
			else
			{
				// maybe not do this every tick.
				Controller->MoveToLocation(TargetLocation);
			}
		}
	}
	else
	{
		if (WaitTimer <= 0.f)
		{
			ChangeState(TEXT("Idle"));
		}
	}

	return Super::TickActive(DeltaTime);
}

void UFGAIStateAttacking::UpdateTargetLocation()
{
	TargetLocation = bHasTarget ? TargetingComp->CurrentTarget->GetActorLocation() : TargetLocation;
}
