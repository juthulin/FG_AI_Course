#include "FGAIGameMode.h"
#include "FGAIGameState.h"

AFGAIGameMode::AFGAIGameMode()
	: Super()
{
	GameStateClass = AFGAIGameState::StaticClass();
}

void AFGAIGameMode::AddNoiseActor(AFGNoiseActor* NoiseActor)
{
	if(!NoiseActorsInWorld.Contains(NoiseActor))
	{
		NoiseActorsInWorld.Add(NoiseActor);
		UE_LOG(LogTemp, Log, TEXT("AFGAIGameMode ADDED a NoiseActor to the list."))
	}
}

void AFGAIGameMode::RemoveNoiseActor(AFGNoiseActor* NoiseActor)
{
	if (NoiseActorsInWorld.Contains(NoiseActor))
	{
		NoiseActorsInWorld.Remove(NoiseActor);
		UE_LOG(LogTemp, Log, TEXT("AFGAIGameMode REMOVED a NoiseActor from the list."))
	}
}

TArray<AFGNoiseActor*> AFGAIGameMode::GetNoiseActors()
{
	return NoiseActorsInWorld;
}