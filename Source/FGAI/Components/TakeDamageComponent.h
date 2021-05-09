#pragma once
#include "Components/ActorComponent.h"
#include "TakeDamageComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UTakeDamageComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	void OnTakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator);
};
