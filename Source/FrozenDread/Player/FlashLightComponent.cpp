//
// FlashLightComponent.cpp
// Implementation of the UFlashLightComponent class.
//

#include "FlashLightComponent.h"

#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UFlashLightComponent::UFlashLightComponent()
{
	// Outer and inner spotlights
	OuterSpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("OuterSpotLightComponent"));
	OuterSpotLightComponent->InnerConeAngle = 0.0F;
	OuterSpotLightComponent->OuterConeAngle = 25.0F;
	OuterSpotLightComponent->SetMobility(EComponentMobility::Movable);
	OuterSpotLightComponent->SetVisibility(IsOn);
	OuterSpotLightComponent->SetupAttachment(this);

	InnerSpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("InnerSpotLightComponent"));
	InnerSpotLightComponent->InnerConeAngle = 0.0F;
	InnerSpotLightComponent->OuterConeAngle = 12.0F;
	InnerSpotLightComponent->SetMobility(EComponentMobility::Movable);
	InnerSpotLightComponent->SetVisibility(IsOn);
	InnerSpotLightComponent->SetupAttachment(this);
	
	// Other settings
	PrimaryComponentTick.bCanEverTick = false;
}

void UFlashLightComponent::PostInitProperties()
{
	Super::PostInitProperties();
	OuterSpotLightComponent->SetupAttachment(this);
	InnerSpotLightComponent->SetupAttachment(this);
}

AActor* UFlashLightComponent::GetActorInRange() const
{
	check(OuterSpotLightComponent);
	check(LightSweepChannel);
	
	FHitResult HitResult;

	const float Range { static_cast<float>(OuterSpotLightComponent->GetBoundingSphere().W * 2) };
	const FVector Direction { OuterSpotLightComponent->GetForwardVector() };
	
	const FVector Start { OuterSpotLightComponent->GetComponentLocation() };
	const FVector End { Start + (Direction * (Range/2)) };

	FCollisionShape CollisionShape;
	const FVector3f HalfExtent { Range / 2, Range / 2, 200.0F };
	CollisionShape.SetBox(HalfExtent);

	const bool bHit { GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, LightSweepChannel, CollisionShape) };

	bool IsInLightRange { false };
	if (bHit)
	{
		// Ensure hit actor is within the cone based on angle
		const FVector ToHitActor { HitResult.GetActor()->GetActorLocation() - GetComponentLocation() };
		const FVector ToHitActorDirection { ToHitActor.GetSafeNormal() };
		const FVector Forward { OuterSpotLightComponent->GetForwardVector() };

		const double AngleBetween { FMath::Acos(Forward.Dot(ToHitActorDirection)) };
		
		if (AngleBetween < OuterSpotLightComponent->GetHalfConeAngle())
		{
			IsInLightRange = true;
		}
	}

	// TODO: Ensure that there is no blocking volume in between
	bool IsLightBlocked = false;

	// Uncomment for debugging
#if !(UE_BUILD_SHIPPING | UE_BUILD_TEST)
	//DrawDebugCone(GetWorld(), Start, Direction, Range, OuterSpotLightComponent->GetHalfConeAngle(), OuterSpotLightComponent->GetHalfConeAngle(), 4, bIsInLightRange ? FColor::Blue : FColor::Red, false, 0, 0);
#endif

	return (IsInLightRange && IsOn && !IsLightBlocked ? HitResult.GetActor() : nullptr);
}

void UFlashLightComponent::Toggle()
{
	IsOn = !IsOn;

	// Play toggle sound
	check(ToggleSound);
	UGameplayStatics::PlaySound2D(this, ToggleSound);

	// Turn spotlights on/off
	InnerSpotLightComponent->SetVisibility(IsOn, true);
	OuterSpotLightComponent->SetVisibility(IsOn, true);
}

