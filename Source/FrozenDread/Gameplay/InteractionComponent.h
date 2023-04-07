//
// InteractionComponent.h
// Definition of the UInteractionComponent class.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class APlayerCharacter;
class UInteractionWidget;
class IInteractiveObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FROZENDREAD_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/** Trigger an interaction event with the current item being looked at */
	void InteractWithCurrentItem() const;

	/** Set an unowned reference to interaction widget to show and hide */
	void SetInteractionWidget(UInteractionWidget* Widget);

private:
	void QueryForInteractiveObjects();
	void SetCurrentInteractiveObject(IInteractiveObject* Object);
	void GetLineTraceFromScreen(FVector& Start, FVector& End) const;
	void UpdateUI() const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	float LineTraceLength { 500 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> CollisionChannel;

private:
	TWeakObjectPtr<APlayerCharacter> PlayerCharacter;
	UInteractionWidget* InteractionWidget;
	IInteractiveObject* CurrentObject { nullptr };
};
