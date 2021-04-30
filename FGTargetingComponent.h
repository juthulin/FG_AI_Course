#pragma once
#include "Components/ActorComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"
#include "FGAI/AI/Sensing/FGHearingSensingComponent.h"
#include "FGAI/AI/Sensing/DamageSenseComponent.h"
#include "FGTargetingComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void Handle_VisionSense(const FFGVisionSensingResults& VisionSenseInfo);
	UFUNCTION()
	void Handle_VisionLost(const FFGVisionSensingResults& VisionSenseInfo);
	UFUNCTION()
	void Handle_DamageSense(const FFGDamageSenseInfo& DamageSenseInfo);
	UFUNCTION()
	void Handle_HearingSense(const FFGHearingSensingResults& HearingSenseInfo);

public:

	UPROPERTY(BlueprintReadOnly)
	UFGVisionSensingComponent* VisionSense;
	UPROPERTY(BlueprintReadOnly)
	UFGHearingSensingComponent* HearingSense;
	UPROPERTY(BlueprintReadOnly)
	UDamageSenseComponent* DamageSense;
	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentTarget;

	FFGHearingSensingResults LatestHeardNoise;
	bool bHeardNoise = false;
	
};
