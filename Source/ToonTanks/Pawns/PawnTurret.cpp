// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"

#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive())
	{
		return;
	}
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	return Distance;
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}