//
// DoorLockStatusWidget.cpp
// Implementation of the UDoorLockStatusWidget class.
//

#include "FrozenDread/UI/DoorLockStatusWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UDoorLockStatusWidget::SetIsLocked(bool bLocked)
{
	UnlockedStatusImage->SetVisibility(bLocked ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	LockedStatusImage->SetVisibility(bLocked ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	IsLocked = bLocked;
}

void UDoorLockStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsLocked(IsLocked);
}
