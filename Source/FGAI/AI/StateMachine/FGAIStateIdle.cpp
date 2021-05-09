#include "FGAIStateIdle.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/Components/FGTargetingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"

void UFGAIStateIdle::Setup()
{
	StateName = TEXT("Idle");
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	Controller = Cast<AAIController>(OwnerPawn->Controller);

	NavComp = Cast<UFGNavMovementComponent>(GetOwner()->GetComponentByClass(UFGNavMovementComponent::StaticClass()));
	TargetingComp = Cast<UFGTargetingComponent>(GetOwner()->GetComponentByClass(UFGTargetingComponent::StaticClass()));
	
	Super::Setup();
}

void UFGAIStateIdle::OnActivated()
{
	Elapsed = Wait;
	
	Super::OnActivated();
}

void UFGAIStateIdle::OnDeactivated()
{
	if (TargetingComp != nullptr)
		TargetingComp->bHeardNoise = false;
	
	Super::OnDeactivated();
}

FName UFGAIStateIdle::TickActive(float DeltaTime)
{
	Elapsed -= DeltaTime;

	if (Elapsed < 0.f)
	{
		FVector RandomLocation = GetRandomReachableLocation(GetOwner()->GetActorLocation());
		UKismetSystemLibrary::DrawDebugLine(GetOwner(), GetOwner()->GetActorLocation(),RandomLocation, FLinearColor::Yellow,5.f);
		Controller->MoveToLocation(RandomLocation);
		RotateTowardsTarget(RandomLocation);
		
		Elapsed = Wait;
	}

	if (TargetingComp != nullptr)
	{
		if (TargetingComp->CurrentTarget != nullptr)
		{
			ChangeState(TEXT("Attacking"));
			return Super::TickActive(DeltaTime);
		}

		if (TargetingComp->bHeardNoise)
		{
			ChangeState(TEXT("Suspicious"));
			return Super::TickActive(DeltaTime);
		}
	}
	
	return Super::TickActive(DeltaTime);
}

FVector UFGAIStateIdle::GetRandomReachableLocation(const FVector Origin)
{
	FVector RandomLocation(Origin);
	const float RandomAngleDeg(FMath::RandRange(0.f, 359.9f));
	FRotator RandomRotation(0.f, RandomAngleDeg, 0.f);
	const float RandomDistance(FMath::RandRange(10.f, 500.f));
	RandomLocation += RandomRotation.Vector() * RandomDistance;

	UKismetSystemLibrary::DrawDebugLine(GetOwner(), Origin, RandomLocation,
		FLinearColor::Yellow, 5.f);

	return RandomLocation;
}