#pragma once
#include "Components/ActorComponent.h"
#include "FGHearingSensingComponent.generated.h"

class AActor;
class AFGNoiseActor;

USTRUCT(BlueprintType)
struct FFGHearingSensingResults
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	AActor* NoiseInstigator;

	UPROPERTY(BlueprintReadOnly)
	FVector NoiseLocation;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSensingDelegate, const FFGHearingSensingResults&, Results);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGHearingSensingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGHearingSensingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSensedNoiseActor(AFGNoiseActor* NoiseActor);
	void RemoveSensedNoiseActor(AFGNoiseActor* NoiseActor);
	
	UPROPERTY(BlueprintAssignable)
	FFGHearingSensingDelegate OnNoiseHeard;
	
	UPROPERTY(EditAnywhere)
	float HearingRange = 1000.f;

	TArray<AFGNoiseActor*> SensedNoiseActors;
};