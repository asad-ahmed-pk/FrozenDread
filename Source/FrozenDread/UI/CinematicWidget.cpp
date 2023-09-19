//
// CinematicWidget.cpp
// Implementation of the UCinematicWidget class.
//

#include "CinematicWidget.h"

void UCinematicWidget::PlayFadeInAnimation()
{
	check(FadeInAnimation);
	PlayAnimation(FadeInAnimation);
}
