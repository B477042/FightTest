// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerCharacter.h"


AGamePlayerCharacter::AGamePlayerCharacter()
{
	//================================
	// Init Default Subobject
	MainCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraSpringArm"));
	TargetLockComponent = CreateDefaultSubobject<UTargetLockComponent>(TEXT("TargetLockComponent"));
	//================================
	// Init Components Tree

	MainCam->SetupAttachment(MainCamSpringArm);
	MainCamSpringArm->SetupAttachment(RootComponent);


	//================================
	// Init Components value

	// Spring Arm
	MainCamSpringArm->SetRelativeLocation(FVector(0, 130, 70));
	MainCamSpringArm->TargetArmLength = 220.0f;
	MainCamSpringArm->ProbeSize = 14.0f;
	MainCamSpringArm->bUsePawnControlRotation = false;
	

	//================================
	// Load Assets
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Body(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_ue4/rp_sophia_rigged_003_ue4.rp_sophia_rigged_003_ue4'"));
	if (SM_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Body.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90.0f), FRotator(0, -90, 0));
	}
	
	//================================
	// Set Normal Default Value
	CurrentVelocity = 78.f;
}

void AGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePlayerCharacter::MoveLeft(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	


	////양수면 앞, 음수면 뒤



	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
//	AFGame(Log, TEXT("left"));

}

void AGamePlayerCharacter::MoveForward(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;


	////양수면 오른쪽, 음수면 왼쪽

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
//	AFGame(Log, TEXT("forwr"));
	//AFGame(Log,TEXT("forwr"));

}

void AGamePlayerCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);

}

void AGamePlayerCharacter::TurnCamera(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
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

void AGamePlayerCharacter::TargetLock()
{
	/*
	* Camerar가 보고 있는 방향으로 Trace를 이용하여 탐지하고 탐지된 결과 중 가장 거리가 가까운 것을 락온한다.
	*/
	
	
	auto world = GetWorld();
	if (!world)
	{
		AFGame(Error, TEXT("world is nullptr"));
		return;
	}
	FVector start = MainCam->GetComponentLocation();
	
	FVector end = (GetActorLocation()-start) + (MainCam->GetForwardVector() * TargetLockComponent->GetForgetRange());
	float half = TargetLockComponent->GetForgetRange();
	FVector halfSize = FVector(half, half, half);
	TArray<AActor*>toIgnore;
	
	//Trace 연산
	UKismetSystemLibrary::BoxTraceSingleForObjects(world,start,end,halfSize,GetActorRotation(),)


	//가장 가까운 것을 타겟으로 


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
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AGamePlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnCamera"), this, &AGamePlayerCharacter::TurnCamera);

	//=============================
	// Action Input Bind
	PlayerInputComponent->BindAction(TEXT("TargetLock"),EInputEvent::IE_Pressed ,this, &AGamePlayerCharacter::TargetLock);

}
