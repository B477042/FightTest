// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ActionFightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONFIGHT_API AActionFightGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AActionFightGameMode();
	virtual void PostLogin(APlayerController* NewPlayer)override;

	virtual void PostInitializeComponents() override;
};
