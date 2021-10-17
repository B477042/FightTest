// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCharacter.h"

AGamePlayerCharacter::AGamePlayerCharacter()
{
	//================================
	// Init Default Subobject
	MainCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"));


	//================================
	// Init Components value

	//================================
	// Load Assets
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Body(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_ue4/rp_sophia_rigged_003_ue4.rp_sophia_rigged_003_ue4'"));
	if (SM_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Body.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90.0f), FRotator(0, -90, 0));
	}
	//================================
	// Init Components Tree

	MainCam->SetupAttachment(MainCamSpringArm);
	MainCamSpringArm->SetupAttachment(RootComponent);

	//================================
	// Set Normal Default Value
	CurrentVelocity = 0.0f;
}

void AGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePlayerCharacter::MoveLeft(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	


	////양수면 앞, 음수면 뒤



	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);

}

void AGamePlayerCharacter::MoveForward(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;


	////양수면 오른쪽, 음수면 왼쪽

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
	//AFGame(Log,TEXT("forwr"));

}

void AGamePlayerCharacter::Move(float DeltaTime)
{
	if (MoveDirection.IsZero()) {
		return;
	}

	MoveDirection.Normalize();
	AddMovementInput(MoveDirection, CurrentVelocity * DeltaTime);
	MoveDirection.Set(0.0f, 0.0f, 0.0f);
}

void AGamePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//=============================
	// Axis Input Bind

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this,&AGamePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &AGamePlayerCharacter::MoveLeft);

}
