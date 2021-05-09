#pragma once
#include "Engine/GameInstance.h"
#include "FGAIGameInstance.generated.h"
class AFGNoiseActor;

UCLASS()
class UFGAIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFGAIGameInstance();

	// Noise Functionalities
	TArray<AFGNoiseActor*> ActiveNoiseActors;

	void AddNoiseActor(AFGNoiseActor* NoiseActor);
	void RemoveNoiseActor(AFGNoiseActor* NoiseActor);
	TArray<AFGNoiseActor*> GetNoiseActors();
};