//
// ExoSuitPickup.h
// Implementation of the AExoSuitPickup class.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FrozenDread/Gameplay/InteractiveObject.h"

#include "ExoSuitPickup.generated.h"

class UBoxComponent;
class UMetaSoundSource;
class USkeletalMeshComponent;

UCLASS()
class FROZENDREAD_API AExoSuitPickup : public AActor, public IInteractiveObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExoSuitPickup();

	virtual void SetHighlighted(bool IsHighlighted) override;

	virtual FText DisplayText() const override;

	virtual void Interact(APlayerCharacter* PlayerCharacter) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	FText HighlightText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties", meta=(AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sounds", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UMetaSoundSource> EquipSound;

private:
	bool bPickedUp { false };
};
