//
// JumpScare.cpp
// Implementation of the AJumpScare class.
//

#include "JumpScareTriggerBox.h"

#include "Components/AudioComponent.h"

// Sets default values
AJumpScareTriggerBox::AJumpScareTriggerBox()
{
	// Audio Component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(GetRootComponent());
		
	// Other settings
	PrimaryActorTick.bCanEverTick = false;
}

void AJumpScareTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!IsTriggerEnabled)
	{
		return;
	}
	
	if (TriggerSound)
	{
		AudioComponent->SetSound(TriggerSound);
		AudioComponent->Play();
	}

	// Deactivate trigger if this is a one-shot jump-scare
	if (IsOneShotTrigger)
	{
		IsTriggerEnabled = false;
	}

	// Notify delegate
	OnJumpScareTriggered.Broadcast();
}

