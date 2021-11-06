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

	// Tick���� ����. Camera�� Target�� ���ϵ��� ȸ��
	virtual void rotateCameraToTarget();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*
	��� Actor�� Ÿ������ �����մϴ�. Ÿ���� �����ȴٸ� Tick�� ���ְ� �˴ϴ�.
	�����ϸ� True, �����ϸ� false
	*/
	bool LockOnTarget(AActor* const  OtherActor);
	/*
	Ÿ���� �ذ� Tick�� ���ݴϴ�.
	Ÿ���� ���� ���¿��� ȣ��Ǹ� false
	ó���ϸ� true
	*/
	bool ReleaseTarget();


protected:
	/*
	* Onwer Character�� springArm
	*/
	UPROPERTY(VisibleAnywhere, Category = "springArm", meta = (AllowPrivateAccess = true))
		TWeakObjectPtr<class USpringArmComponent>springArm;

	/*
	*	������ ������ Actor
	*/

	UPROPERTY(VisibleAnywhere, Category = "Target")
		TWeakObjectPtr<AActor> targetActor;
	//�� �Ÿ���ŭ �־����� �ذ� �˴ϴ�. Ÿ�ٰ� �Ÿ��� �� �Ÿ����� �ִٸ� ������ �� �����ϴ�. �⺻�� 7m
	UPROPERTY(EditAnywhere, Category = "Target", meta = (AllowPrivateAccess = true))
		float forgetRange;
};
