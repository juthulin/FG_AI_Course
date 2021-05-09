#include "ShootComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TakeDamageComponent.h"
#include "FGAI/FGNoiseActor.h"

void UShootComponent::Shoot(FVector Start, FVector Direction)
{
	AFGNoiseActor::SpawnNoise(GetOwner());
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(this, Start, Start + Direction * ShootRange, TraceType,
		false, IgnoreActors, EDrawDebugTrace::ForDuration, Hit, true);

	if (Hit.bBlockingHit && Hit.GetActor() != nullptr)
	{
		auto* TakeDamage = Cast<UTakeDamageComponent>(Hit.GetActor()->GetComponentByClass(UTakeDamageComponent::StaticClass()));
		if (TakeDamage != nullptr)
		{
			TakeDamage->OnTakeDamage(Hit, 10.f, GetOwner());
		}
	}
}
