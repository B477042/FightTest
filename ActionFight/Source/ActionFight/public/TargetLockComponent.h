// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionFight.h"
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

	// Tick에서 동작. Camera가 Target을 향하도록 회전
	virtual void rotateCameraToTarget();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*
	대상 Actor를 타겟으로 설정합니다. 타겟이 설정된다면 Tick을 켜주게 됩니다.
	성공하면 True, 실패하면 false
	*/
	bool LockOnTarget(AActor* const  OtherActor);
	/*
	타겟을 잊고 Tick을 꺼줍니다.
	타겟이 없는 상태에서 호출되면 false
	처리하면 true
	*/
	bool ReleaseTarget();


protected:
	/*
	* Onwer Character의 springArm
	*/
	UPROPERTY(VisibleAnywhere, Category = "springArm", meta = (AllowPrivateAccess = true))
		TWeakObjectPtr<class USpringArmComponent>springArm;

	/*
	*	시점이 고정될 Actor
	*/

	UPROPERTY(VisibleAnywhere, Category = "Target")
		TWeakObjectPtr<AActor> targetActor;
	//이 거리만큼 멀어지면 잊게 됩니다. 타겟과 거리가 이 거리보다 멀다면 설정할 수 없습니다. 기본값 7m
	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
		float forgetRange;
};
