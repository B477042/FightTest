// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\ActionFight.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "TargetLockComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONFIGHT_API UTargetLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetLockComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Tick���� ����. Camera�� Target�� ���ϵ��� ȸ��
	virtual void rotateCameraToTarget();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool LockOnTarget(AActor* const  OtherActor);
	bool ReleaseTarget();


protected:
	/*
	* Onwer Character�� SpringArm
	*/
	UPROPERTY(VisibleAnywhere, Category = "SpringArm", meta = (AllowPrivateAccess = true))
		TWeakObjectPtr<class USpringArmComponent>SpringArm;

	/*
	*	������ ������ Actor
	*/

	UPROPERTY(VisibleAnywhere, Category = "Target")
		TWeakObjectPtr<AActor> TargetActor;

};
