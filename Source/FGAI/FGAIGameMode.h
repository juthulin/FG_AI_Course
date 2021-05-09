// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGAIGameMode.generated.h"
class AFGNoiseActor;

UCLASS(minimalapi)
class AFGAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFGAIGameMode();
	virtual ~AFGAIGameMode() = default;


	// Noise Functionalities.
	TArray<AFGNoiseActor*> NoiseActorsInWorld;

	void AddNoiseActor(AFGNoiseActor* NoiseActor);
	void RemoveNoiseActor(AFGNoiseActor* NoiseActor);
	TArray<AFGNoiseActor*> GetNoiseActors();
};