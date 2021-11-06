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
	* 카메라가 타겟을 향하도록 업데이트를 해줍니다. 만약 타겟이 일정 범위를 벗어난다면 잊게 됩니다.
	*/
	if (!GetOwner())
	{
		AFGame(Error, TEXT("Owner is nullptr"));
		return ;
	}

	//거리 검사
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

	//거리 검사
	float toTarget = FVector::Dist(GetOwner()->GetActorLocation(), OtherActor->GetActorLocation());
	if (toTarget > forgetRange)
	{
		AFGame(Log, TEXT("Other actor is too far"));
		return false;
	}

	//이전에 설정된 Target이 있다면 새로 고쳐줍니다.
	if (targetActor.IsValid())
	{
		targetActor.Get();
	}
	//Set New Target actor
	targetActor = OtherActor;

	//Spring Arm의 회전을 자유롭게 해줍니다
	springArm->bUsePawnControlRotation = false;
	SetComponentTickEnabled(true);

	return true;
}

bool UTargetLockComponent::ReleaseTarget()
{
	//타겟을 잊습니다
	if (targetActor.IsValid())
	{
		springArm->bUsePawnControlRotation = true;
		targetActor.Get();
		SetComponentTickEnabled(false);
		return true;
	}

	return false;
}

