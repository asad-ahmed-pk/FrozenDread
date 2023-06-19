//
// GameOverWidget.cpp
// Implementation of the UGameOverWidget class.
//

#include "FrozenDread/UI/GameOverWidget.h"

void UGameOverWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(Animation);
}
