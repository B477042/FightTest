// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLockComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UTargetLockComponent::UTargetLockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	forgetRange = 700.0f;
	// ...
}


// Called when the game starts
void UTargetLockComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetComponentTickEnabled ( false);

}

void UTargetLockComponent::rotateCameraToTarget()
{
	if (!springArm.IsValid())
	{
		AFGame(Error, TEXT("Spring Arm is invalid"));
		SetComponentTickEnabled(false);
		return;
	}
	if (!targetActor.IsValid())
	{
		AFGame(Error, TEXT("targetActor is invalid"));
		SetComponentTickEnabled(false);
		return;
	}

	/*
	* ī�޶� Ÿ���� ���ϵ��� ������Ʈ�� ���ݴϴ�. ���� Ÿ���� ���� ������ ����ٸ� �ذ� �˴ϴ�.
	*/
	if (!GetOwner())
	{
		AFGame(Error, TEXT("Owner is nullptr"));
		return ;
	}

	//�Ÿ� �˻�
	float toTarget = FVector::Dist(GetOwner()->GetActorLocation(), targetActor->GetActorLocation());
	if (toTarget > forgetRange)
	{
		AFGame(Log, TEXT("Other actor is too far"));
		ReleaseTarget();
		return;
	}

	


}


// Called every frame
void UTargetLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	rotateCameraToTarget();

	// ...
}


bool UTargetLockComponent::LockOnTarget(AActor* const OtherActor)
{
	if (!OtherActor)
	{
		AFGame(Error, TEXT("Other Actor is nullptr"));
		return false;
	}
	
	if (!springArm.IsValid())
	{
		AFGame(Error, TEXT("SPring Arm is nullptr "));
		return false;
	}
	if (!GetOwner())
	{
		AFGame(Error, TEXT("Owner is nullptr"));
		return false;
	}

	//�Ÿ� �˻�
	float toTarget = FVector::Dist(GetOwner()->GetActorLocation(), OtherActor->GetActorLocation());
	if (toTarget > forgetRange)
	{
		AFGame(Log, TEXT("Other actor is too far"));
		return false;
	}

	//������ ������ Target�� �ִٸ� ���� �����ݴϴ�.
	if (targetActor.IsValid())
	{
		targetActor.Get();
	}
	//Set New Target actor
	targetActor = OtherActor;

	//Spring Arm�� ȸ���� �����Ӱ� ���ݴϴ�
	springArm->bUsePawnControlRotation = false;
	SetComponentTickEnabled(true);

	return true;
}

bool UTargetLockComponent::ReleaseTarget()
{
	//Ÿ���� �ؽ��ϴ�
	if (targetActor.IsValid())
	{
		springArm->bUsePawnControlRotation = true;
		targetActor.Get();
		SetComponentTickEnabled(false);
		return true;
	}

	return false;
}

