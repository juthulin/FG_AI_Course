#include "TakeDamageComponent.h"
#include "HealthComponent.h"
#include "FGAI/AI/Sensing/DamageSenseComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UTakeDamageComponent::OnTakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator)
{
	auto* Health = Cast<UHealthComponent>(GetOwner()->GetComponentByClass(UHealthComponent::StaticClass()));
	if (Health != nullptr)
	{
		Health->Health -= Damage;
	}

	auto* DamageSense = Cast<UDamageSenseComponent>(GetOwner()->GetComponentByClass(UDamageSenseComponent::StaticClass()));
	if (DamageSense != nullptr)
	{
		FFGDamageSenseInfo SenseInfo;
		SenseInfo.DamageDirection = (Hit.TraceStart - Hit.ImpactPoint).GetSafeNormal();
		SenseInfo.DamageInstigator = DamageInstigator;
		SenseInfo.DamageImpactLocation = Hit.ImpactPoint;
		DamageSense->OnDamageSensed.Broadcast(SenseInfo);
		UKismetSystemLibrary::DrawDebugArrow(this, SenseInfo.DamageImpactLocation,
			SenseInfo.DamageImpactLocation + SenseInfo.DamageDirection * 200.f, 5,
			FLinearColor::Red,2, 5);
	}
}
