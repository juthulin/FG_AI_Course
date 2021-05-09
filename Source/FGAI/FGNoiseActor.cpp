#include "FGNoiseActor.h"

#include "FGAIGameInstance.h"
#include "AI/Sensing/FGHearingSensingComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AFGNoiseActor::AFGNoiseActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootComp;
}

void AFGNoiseActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LifeSpan);

	// subscribe to GameInstance list of NoiseActors.
	UFGAIGameInstance* GI = Cast<UFGAIGameInstance>(GetWorld()->GetGameInstance());
	if (GI == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("UFGAIGameInstance* 'GI' variable was nullptr when trying to add NoiseActor to list."));
		return;
	}
	
	GI->AddNoiseActor(this);
}

void AFGNoiseActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	// unsubscribe to GameMode list of NoiseActors.
	UFGAIGameInstance* GI = Cast<UFGAIGameInstance>(GetWorld()->GetGameInstance());
	if (GI == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("UFGAIGameInstance* 'GI' variable was nullptr when trying to remove NoiseActor from list."));
		return;
	}

	NotifyDetectorsOfDestroy();
	
	GI->RemoveNoiseActor(this);
}

void AFGNoiseActor::RegisterDetection(UFGHearingSensingComponent* Detector)
{
	Detectors.Add(Detector);
	Detector->AddSensedNoiseActor(this);
}

void AFGNoiseActor::NotifyDetectorsOfDestroy()
{
	if (Detectors.Num() == 0)
		return;
	
	for (auto* Detector : Detectors)
	{
		Detector->RemoveSensedNoiseActor(this);
	}
	// The expression below removes every single Detector just before this NoiseActor gets destroyed.
	// I don't know if this affects performance positively or negatively or if it's just unnecessary.
	Detectors.Empty();
}

void AFGNoiseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation(), StartRadius, 12,
		FLinearColor::Green);
}

void AFGNoiseActor::SpawnNoise(AActor* NoiseInstigator)
{
	auto* Noise = NoiseInstigator->GetWorld()->SpawnActor<AFGNoiseActor>(NoiseInstigator->GetActorLocation(), FRotator::ZeroRotator);
	Noise->NoiseInstigator = NoiseInstigator;
}