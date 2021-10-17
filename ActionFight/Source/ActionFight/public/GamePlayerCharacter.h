// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GamePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONFIGHT_API AGamePlayerCharacter : public AGameCharacter
{
	GENERATED_BODY()
public:
	AGamePlayerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//===================================
	// Axis Input
	void MoveLeft(float NewAxisValue);
	void MoveForward(float NewAxisValue);
	
	//===================================
	// Movement
	void Move(float DeltaTime);


	//===================================
	// Action Input




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
		UCameraComponent* MainCam;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
		USpringArmComponent* MainCamSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		FVector MoveDirection;
	float CurrentVelocity;

};
