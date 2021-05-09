#pragma once
#include "GameFramework/GameState.h"
#include "FGAIGameState.generated.h"

UCLASS()
class AFGAIGameState : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFGAIGameState();
	virtual ~AFGAIGameState() = default;
};
