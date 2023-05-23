//
// DoorLockStatusWidget.h
// Definition of the UDoorLockStatusWidget class.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DoorLockStatusWidget.generated.h"

class UImage;
class UCanvasPanel;

/**
 * UMG Widget for displaying in-game world UI for the door's lock / unlock status.
 */
UCLASS()
class FROZENDREAD_API UDoorLockStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetIsLocked(bool bLocked);
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> LockedStatusImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> UnlockedStatusImage;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvas;

private:
	bool IsLocked { true };
};
