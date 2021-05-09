#pragma once
#include "Components/ActorComponent.h"
#include "DamageSenseComponent.generated.h"

USTRUCT(BlueprintType)
struct FFGDamageSenseInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* DamageInstigator;

	UPROPERTY(BlueprintReadOnly)
	FVector DamageDirection;

	UPROPERTY(BlueprintReadOnly)
	FVector DamageImpactLocation;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGOnDamageSenseDelegate, const FFGDamageSenseInfo&, DamageSenseInfo);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UDamageSenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FFGOnDamageSenseDelegate OnDamageSensed;
};
