#pragma once
#include "FGAIStateBase.h"
#include "FGAIStateAttacking.generated.h"

class AAIController;
class UFGTargetingComponent;

UCLASS()
class UFGAIStateAttacking : public UFGAIStateBase
{
	GENERATED_BODY()
public:

	FName InStateName = TEXT("Attacking");

	AAIController* Controller;
	UFGTargetingComponent* TargetingComp;

	virtual void Setup() override;
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual FName TickActive(float DeltaTime) override;

private:

	bool bHasTarget = false;
	bool bIsAttacking = false;
	FVector TargetLocation;
	const float WaitAfterAttackMax = 2.f;
	const float WaitAfterMoveMax = 2.f;
	float WaitTimer = 0.f;
	const float TimeBetweenUpdates = .5f;
	float UpdateTimer;

	void UpdateTargetLocation();
};
