// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PawnTank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
public:

	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float moveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float rotateSpeed = 100.0f;
	FVector MoveDirection;
	FQuat RotationDirection;
	APlayerController* PlayerControllerRef;
	FHitResult TraceHitResult;
	void CalculateMovementInput(float value);
	void CalculateRotateInput(float value);
	void Move();
	void Rotate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleDestruction() override;
};
