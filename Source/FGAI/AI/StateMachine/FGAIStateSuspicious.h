#pragma once
#include "FGAIStateBase.h"
#include "FGAIStateSuspicious.generated.h"

class AAIController;
class UFGTargetingComponent;

UCLASS()
class UFGAIStateSuspicious : public UFGAIStateBase
{
	GENERATED_BODY()

public:

	AAIController* Controller;
	UFGTargetingComponent* TargetingComp;

	virtual void Setup() override;

	virtual void OnActivated() override;

	virtual void OnDeactivated() override;

	virtual FName TickActive(float DeltaTime) override;

private:

	FVector FirstNoiseLocation;
	float RemainingWaitTime{0.f};
	const float TimeToWait{3.f};
};
