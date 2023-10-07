//
// CinematicWidget.cpp
// Implementation of the UCinematicWidget class.
//

#include "CinematicWidget.h"

#include "Animation/UMGSequencePlayer.h"

void UCinematicWidget::PlayFadeInAnimation(const TFunction<void()>& Callback)
{
	check(FadeInAnimation);
	AnimationCompletionCallback = Callback;
	PlayAnimation(FadeInAnimation);
}

void UCinematicWidget::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);
	if (Player.GetAnimation() == FadeInAnimation)
	{
		AnimationCompletionCallback();
	}
}
