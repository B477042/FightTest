// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionFightGameMode.h"
#include "..\Actor\GamePlayerCharacter.h"
#include "..\Actor\GamePlayerController.h"
#include "AFGameState.h"
#include "AFPlayerState.h"

AActionFightGameMode::AActionFightGameMode()
{
	DefaultPawnClass = AGamePlayerCharacter::StaticClass();
	PlayerControllerClass = AGamePlayerController::StaticClass();
	GameStateClass = AAFGameState::StaticClass();
	PlayerStateClass = AAFGameState::StaticClass();
}

void AActionFightGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AActionFightGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
