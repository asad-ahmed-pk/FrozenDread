//
// CinematicWidget.h
// Definition of the UCinematicWidget class.
//

#pragma once

class UWidgetAnimation;

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CinematicWidget.generated.h"

/**
 * Widget responsible for displaying cinematic effects.
 */
UCLASS()
class FROZENDREAD_API UCinematicWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Play the fade in animation and call the callback once completed */
	void PlayFadeInAnimation(const TFunction<void()>& Callback);

protected:
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;

protected:
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeInAnimation;

private:
	TFunction<void()> AnimationCompletionCallback;
};
