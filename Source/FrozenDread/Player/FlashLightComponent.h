//
// FlashLightComponent.h
// Definition of the UFlashLightComponent class.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlashLightComponent.generated.h"

class USoundBase;
class USpotLightComponent;

/**
 * Component for providing a flashlight that can be toggled on and off.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FROZENDREAD_API UFlashLightComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFlashLightComponent();

	virtual void PostInitProperties() override;

	/** Toggle the flashlight on or off */
	void Toggle();

private:
	/** The sound to play when the flash light is toggled on and off manually */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> ToggleSound;

	/** The outer spotlight for this flashlight */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Light", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpotLightComponent> OuterSpotLightComponent;

	/** The inner spotlight for this flashlight */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Light", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpotLightComponent> InnerSpotLightComponent;

private:
	bool IsOn { false }; 
};
