// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionFight.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONFIGHT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AGamePlayerController();
	
	virtual void PostInitializeComponents()override;

protected:
	virtual void BeginPlay();
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn)override;


};
