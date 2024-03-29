﻿//
// FlashLightComponent.cpp
// Implementation of the UFlashLightComponent class.
//

#include "FlashLightComponent.h"

#include "Components/SpotLightComponent.h"
#include "FrozenDread/Game/GameOptions.h"
#include "FrozenDread/System/GameSettingsSubsystem.h"
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

	LumenIntensityInner = InnerSpotLightComponent->Intensity;
	LumenIntensityOuter = OuterSpotLightComponent->Intensity;
}

void UFlashLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register for changes to the game settings (to adjust light strength when lumen setting changes)
	FGameSettingsDelegate::OnGameSettingsChanged.AddUObject(this, &UFlashLightComponent::UpdateFlashLightStrengthForGameSetting);
	UpdateFlashLightStrengthForGameSetting();
}

AActor* UFlashLightComponent::GetActorInRange() const
{
	// Uncomment for debugging
	#if !(UE_BUILD_SHIPPING | UE_BUILD_TEST)
	//DrawDebugCone(GetWorld(), Start, Direction, Range, OuterSpotLightComponent->GetHalfConeAngle(), OuterSpotLightComponent->GetHalfConeAngle(), 4, bIsInLightRange ? FColor::Blue : FColor::Red, false, 0, 0);
	#endif

	// Sweep by set channel to find target actor
	if (AActor* TargetActor { GetHitActorBySweep(LightSweepChannel) })
	{
		// The offset from the flashlight to avoid collision with player's character
		static constexpr float OFFSET { 20.0F };
		
		const FVector FlashlightStart { GetComponentLocation() + GetForwardVector() * OFFSET };
		const bool IsBlocked { IsBlockedByStaticObject(TargetActor, FlashlightStart) };

		// Ensure hit actor is within the cone based on angle
		const FVector ToHitActor { TargetActor->GetActorLocation() - GetComponentLocation() };
		const FVector ToHitActorDirection { ToHitActor.GetSafeNormal() };
		const FVector Forward { OuterSpotLightComponent->GetForwardVector() };

		const double AngleBetween { FMath::Acos(Forward.Dot(ToHitActorDirection)) };
		
		if (AngleBetween < OuterSpotLightComponent->GetHalfConeAngle())
		{
			return (IsOn && !IsBlocked ? TargetActor : nullptr);
		}
	}

	return nullptr;
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

void UFlashLightComponent::UpdateFlashLightStrengthForGameSetting()
{
	static constexpr float NON_LUMEN_SCALE_FACTOR { 3.0F };
	
	const auto GraphicsOptions { UGameSettingsSubsystem::GetGraphicsOptions() };

	check(InnerSpotLightComponent);
	check(OuterSpotLightComponent);
	
	InnerSpotLightComponent->SetIntensity(GraphicsOptions.EnableLumen ? LumenIntensityInner : LumenIntensityInner * NON_LUMEN_SCALE_FACTOR);
	OuterSpotLightComponent->SetIntensity(GraphicsOptions.EnableLumen ? LumenIntensityOuter : LumenIntensityOuter * NON_LUMEN_SCALE_FACTOR);
}

bool UFlashLightComponent::IsBlockedByStaticObject(const AActor* TargetActor, const FVector& Start) const
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, TargetActor->GetActorLocation(), ECC_WorldStatic);
	return HitResult.bBlockingHit && HitResult.GetActor() != TargetActor;
}

AActor* UFlashLightComponent::GetHitActorBySweep(ECollisionChannel Channel) const
{
	check(OuterSpotLightComponent);
	
	FHitResult HitResult;

	const float Range { static_cast<float>(OuterSpotLightComponent->GetBoundingSphere().W * 2) };
	const FVector Direction { OuterSpotLightComponent->GetForwardVector() };
	
	const FVector Start { OuterSpotLightComponent->GetComponentLocation() };
	const FVector End { Start + (Direction * (Range/2)) };

	FCollisionShape CollisionShape;
	const FVector3f HalfExtent { Range / 2, Range / 2, 200.0F };
	CollisionShape.SetBox(HalfExtent);
	
	const bool IsHit { GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, Channel, CollisionShape) };
	if (IsHit)
	{
		return HitResult.GetActor();
	}

	return nullptr;
}

