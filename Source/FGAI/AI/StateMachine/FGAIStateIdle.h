#pragma once
#include "FGAIStateBase.h"
#include "FGAIStateIdle.generated.h"

class AAIController;
class UFGTargetingComponent;
class UFGNavMovementComponent;

UCLASS()
class UFGAIStateIdle : public UFGAIStateBase
{
	GENERATED_BODY()

public:

	AAIController* Controller;
	UFGTargetingComponent* TargetingComp;
	UFGNavMovementComponent* NavComp;

	float Elapsed = 0.f;
	float Wait = 3.f;

	virtual void Setup() override;

	virtual void OnActivated() override;

	virtual void OnDeactivated() override;

	virtual FName TickActive(float DeltaTime) override;

private:

	FVector GetRandomReachableLocation(const FVector Origin);
};