// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ActionFight.h"

#include "ProjectileBaseActor.generated.h"
class AActor;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class UArrowComponent;

UCLASS()
class ACTIONFIGHT_API AProjectileBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
protected:
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		UProjectileMovementComponent* MovementComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VFX")
		UParticleSystemComponent* VFX_MainTrace;
	UPROPERTY(VisibleAnywhere, Category = "Arrow")
		UArrowComponent* ArrowComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VFX")
		UAudioComponent* SFX_Hit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VFX")
		UAudioComponent* SFX_Passing;
	UPROPERTY(VisibleAnywhere)
		uint8 bIsFired : 1;
};
