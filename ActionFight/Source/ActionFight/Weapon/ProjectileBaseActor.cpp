// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBaseActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AProjectileBaseActor::AProjectileBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//================================
	//Init Default subobject

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	VFX_MainTrace = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainTrace"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SFX_Hit = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Hit"));
	SFX_Passing = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Passing"));

	//================================
	// Component Tree

	RootComponent = VFX_MainTrace;
	ArrowComponent->SetupAttachment(RootComponent);
	SFX_Hit->SetupAttachment(RootComponent);
	SFX_Passing->SetupAttachment(RootComponent);



	//================================
	// Actor&Component Default Value

	VFX_MainTrace->bAutoActivate = false;
	SFX_Hit->bAutoActivate = false;
	SFX_Passing->bAutoActivate = false;

	bIsFired = false;


	//================================
	// Load Asset
	


}

// Called when the game starts or when spawned
void AProjectileBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

