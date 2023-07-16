//
// JumpScare.h
// Definition of the AJumpScare class.
//

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "JumpScareTriggerBox.generated.h"

class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJumpScareTriggerBoxDelegate);

/**
 * Trigger box that plays a jump-scare sound when the player enters an area
 */
UCLASS()
class FROZENDREAD_API AJumpScareTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJumpScareTriggerBox();

	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	/** Called when the jump scare is triggered */
	UPROPERTY(BlueprintAssignable, Category="Jumpscare", meta=(AllowPrivateAccess="true"))
	FJumpScareTriggerBoxDelegate OnJumpScareTriggered;
	
	/** Set to play the sound when player triggers the jump scare */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Jumpscare", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> TriggerSound;

	/** The audio component that will play the sounds */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Jumpscare", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAudioComponent> AudioComponent;

	/** Set to true to only trigger once */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Jumpscare", meta=(AllowPrivateAccess="true"))
	bool IsOneShotTrigger { true };

private:
	bool IsTriggerEnabled { true };
};
