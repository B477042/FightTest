// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLockComponent.h"

// Sets default values for this component's properties
UTargetLockComponent::UTargetLockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
	if (!SpringArm.IsValid())
	{
		AFGame(Error, TEXT("Spring Arm is invalid"));
		SetComponentTickEnabled(false);
		return;
	}





}


// Called every frame
void UTargetLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTargetLockComponent::LockOnTarget(AActor* const OtherActor)
{
	if (!OtherActor)
	{
		AFGame(Error, TEXT("Other Actor is nullptr")));
		return false;
	}
	//Check Spring Arm is valid
	if (!SpringArm.IsValid())
	{
		AFGame(Error, TEXT("SPring Arm is nullptr "));
		return false;
	}

	//Forget previous target actor
	if (TargetActor.IsValid())
	{
		TargetActor.Get();
	}
	//Set New Target actor
	TargetActor = OtherActor;

	
	SetComponentTickEnabled(true);

	return true;
}

bool UTargetLockComponent::ReleaseTarget()
{
	if (TargetActor.IsValid())
	{
		TargetActor.Get();
		return true;
	}


	SetComponentTickEnabled(false);

	return false;
}

