#pragma once
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Shoot(FVector Start, FVector Direction);

	UPROPERTY(EditAnywhere)
	float ShootRange = 1000.f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETraceTypeQuery> TraceType;
};
