#include "FGAIGameInstance.h"

UFGAIGameInstance::UFGAIGameInstance() : Super() // Hope this doesn't break anything.
{
}

void UFGAIGameInstance::AddNoiseActor(AFGNoiseActor* NoiseActor)
{
	if(ActiveNoiseActors.Contains(NoiseActor) == false)
	{
		ActiveNoiseActors.Add(NoiseActor);
		UE_LOG(LogTemp, Log, TEXT("UFGAIGameInstance ADDED a NoiseActor to the list!"))
	}
}

void UFGAIGameInstance::RemoveNoiseActor(AFGNoiseActor* NoiseActor)
{
	if(ActiveNoiseActors.Contains(NoiseActor))
	{
		ActiveNoiseActors.Remove(NoiseActor);
		UE_LOG(LogTemp, Log, TEXT("UFGAIGameInstance REMOVED a NoiseActor from the list!"))
	}
}

TArray<AFGNoiseActor*> UFGAIGameInstance::GetNoiseActors()
{
	return ActiveNoiseActors;
}
