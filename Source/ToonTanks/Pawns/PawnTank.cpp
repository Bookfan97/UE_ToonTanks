// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);
	}
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMovementInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMovementInput(float value)
{
	MoveDirection = FVector(value * moveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float value)
{
	float rotateAmount = value * rotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, rotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
}