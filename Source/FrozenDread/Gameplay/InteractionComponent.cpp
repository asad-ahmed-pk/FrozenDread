//
// InteractionComponent.h
// Implementation of the UInteractionComponent class.
//

#include "FrozenDread/Gameplay/InteractionComponent.h"

#include "FrozenDread/Gameplay/InteractiveObject.h"
#include "FrozenDread/Player/GamePlayerController.h"
#include "FrozenDread/Player/PlayerCharacter.h"
#include "FrozenDread/UI/InteractionWidget.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = CastChecked<APlayerCharacter>(GetOwner());
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
										  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter.IsValid())
	{
		QueryForInteractiveObjects();
		UpdateUI();
	}
}

void UInteractionComponent::InteractWithCurrentItem() const
{
	if (CurrentObject != nullptr) {
		CurrentObject->Interact(PlayerCharacter.Get());
	}
}

void UInteractionComponent::SetInteractionWidget(UInteractionWidget* Widget)
{
	InteractionWidget = Widget;
	InteractionWidget->Show(false);
}

void UInteractionComponent::SetCurrentInteractiveObject(IInteractiveObject* Object)
{
	if (CurrentObject != nullptr)
	{
		if (CurrentObject != Object)
		{
			CurrentObject->SetHighlighted(false);
		}
		else
		{
			CurrentObject->SetHighlighted(true);
		}
	}

	CurrentObject = Object;
}

void UInteractionComponent::UpdateUI() const
{
	if (CurrentObject != nullptr)
	{
		if (InteractionWidget)
		{
			const FString String { FString::Printf(TEXT("[E] %s"), *CurrentObject->DisplayText().ToString()) };
			const FText Text { FText::FromString(String) };

			InteractionWidget->SetInteractionText(Text);
			InteractionWidget->Show(true);

			return;
		}
	}

	InteractionWidget->Show(false);
}

void UInteractionComponent::QueryForInteractiveObjects()
{
	FHitResult Hit;

	FVector Start;
	FVector End;
	GetLineTraceFromScreen(Start, End);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(PlayerCharacter.Get());

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, CollisionChannel, QueryParams);

#if !(UE_BUILD_SHIPPING | UE_BUILD_TEST)
	//DrawDebugLine(GetWorld(), Start, End, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 0, 0, 10.0f);
#endif

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		if (IInteractiveObject* InteractiveObject { Cast<IInteractiveObject>(Hit.GetActor()) })
		{
			SetCurrentInteractiveObject(InteractiveObject);
			return;
		}
	}

	SetCurrentInteractiveObject(nullptr);
}

// Get the line trace start position from the center of the view port
void UInteractionComponent::GetLineTraceFromScreen(FVector& Start, FVector& End) const
{
	const UGameViewportClient* Viewport { GetWorld()->GetGameViewport() };
	check(Viewport);
	
	FVector2D ViewportSize;
	Viewport->GetViewportSize(ViewportSize);

	const FVector2D Center { ViewportSize / 2 };

	check(PlayerCharacter.IsValid());
	const AGamePlayerController* PlayerController { PlayerCharacter->GetController<AGamePlayerController>() };

	check(PlayerController);

	FVector WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(Center.X, Center.Y, Start, WorldDirection);

	End = Start + (WorldDirection * LineTraceLength);
}

