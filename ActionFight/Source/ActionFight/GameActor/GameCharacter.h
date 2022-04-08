// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ActionFight.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "GameCharacter.generated.h"

class UStatComponent;
class UStateComponent;


UCLASS(Abstract)
class ACTIONFIGHT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	UPROPERTY(VisibleAnywhere, Category = "Arrow")
		UArrowComponent* RootArrowComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
		UStatComponent* StatComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "State", meta = (AllowPrivateAccess = true))
		UStateComponent* StateComponent;
};
