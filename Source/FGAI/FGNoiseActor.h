#pragma once
#include "GameFramework/Actor.h"
#include "FGNoiseActor.generated.h"
class UFGHearingSensingComponent;

UCLASS()
class AFGNoiseActor : public AActor
{
	GENERATED_BODY()
public:
	AFGNoiseActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void RegisterDetection(UFGHearingSensingComponent* Detector);
	void NotifyDetectorsOfDestroy();

	UFUNCTION(BlueprintCallable)
	static void SpawnNoise(AActor* NoiseInstigator);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly)
	float StartRadius = 300.f;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 1.2f;

	AActor* NoiseInstigator;

	TArray<UFGHearingSensingComponent*> Detectors;
};
