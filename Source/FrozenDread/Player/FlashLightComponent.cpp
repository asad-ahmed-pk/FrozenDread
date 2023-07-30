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

