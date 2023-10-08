//
// LevelCoordinator.cpp
// Implementation of the ALevelCoordinator class.
//

#include "FrozenDread/Level/LevelCoordinator.h"

#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

void ALevelCoordinator::Init(const FSubsystemCache& SubsystemCacheRef)
{
	SubsystemCache = SubsystemCacheRef;
}

void ALevelCoordinator::PlayerInteractedWithDoor(uint8 DoorID, EDoorLockState DoorLockState)
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::PlayerInteractedWithDoor called. Please override in child class."));
}

void ALevelCoordinator::PlayerIntroSequenceCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::PlayerControllerSetupComplete called. Please override in child class."));
}

void ALevelCoordinator::TriggerGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::TriggerGameOver called. Please override in child class."));
}

void ALevelCoordinator::PlayLevelSequence(ULevelSequence* LevelSequence, const TFunction<void(ULevelSequence*)>& CompletionCallback)
{
	if (SequencePlayer == nullptr)
	{
		ALevelSequenceActor* OutActor;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, {}, OutActor);
		SequenceActor = OutActor;
	}
	else
	{
		SequenceActor->SetSequence(LevelSequence);
	}

	SequencePlayer->OnFinished.AddDynamic(this, &ALevelCoordinator::LevelSequenceFinishedPlaying);
	SequencePlayer->Play();

	CurrentPlayingLevelSequence = LevelSequence;
	LevelSequenceCallback = CompletionCallback;
}


void ALevelCoordinator::PlayerInteractedWithItem(uint8 ItemID, AInteractionItem* Item)
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::PlayerInteractedWithItem called. Please override in child class."));
}

void ALevelCoordinator::OnTriggerVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ALevelCoordinator::OnTriggerVolumeBeginOverlap called. Please override in child class."));
}

void ALevelCoordinator::LevelSequenceFinishedPlaying()
{
	if (CurrentPlayingLevelSequence.IsValid())
	{
		LevelSequenceCallback(CurrentPlayingLevelSequence.Get());
	}
}
