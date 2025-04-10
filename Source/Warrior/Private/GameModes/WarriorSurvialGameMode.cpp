// Wyy All Rights Reserved


#include "GameModes/WarriorSurvialGameMode.h"

void AWarriorSurvialGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorSurvialGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWarriorSurvialGameMode::SetCurrentCurrentSurvialGameModeState(EWarriorSurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;
	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);
}
