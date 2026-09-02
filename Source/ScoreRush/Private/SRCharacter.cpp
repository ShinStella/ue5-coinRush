// Fill out your copyright notice in the Description page of Project Settings.


#include "SRCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "SRGameInstance.h"
#include "SRPlayerController.h"

ASRCharacter::ASRCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp->bUsePawnControlRotation = false;
}

void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		CurrentHP = SRGameInstance->GetSRCurrentHP();
		MaxHP = SRGameInstance->GetSRMaxHP();
	}
}

void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetController()))
		{
			if (SRPlayerController->MoveInput)
			{
				EnhancedInput->BindAction(SRPlayerController->MoveInput, ETriggerEvent::Triggered, this, &ASRCharacter::OnMove);
			}
			if (SRPlayerController->LookInput)
			{
				EnhancedInput->BindAction(SRPlayerController->LookInput, ETriggerEvent::Triggered, this, &ASRCharacter::OnLook);
			}
			if (SRPlayerController->JumpInput)
			{
				EnhancedInput->BindAction(SRPlayerController->JumpInput, ETriggerEvent::Triggered, this, &ASRCharacter::OnStartJump);
				EnhancedInput->BindAction(SRPlayerController->JumpInput, ETriggerEvent::Completed, this, &ASRCharacter::OnStopJump);
			}
		}
	}
}

void ASRCharacter::OnMove(const FInputActionValue& Value)
{
	if (!GetController())
	{
		return;
	}

	FVector2D Input = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(Input.X))
	{
		AddMovementInput(GetActorForwardVector(), Input.X);
	}

	if (!FMath::IsNearlyZero(Input.Y))
	{
		AddMovementInput(GetActorRightVector(), Input.Y);
	}
}

void ASRCharacter::OnLook(const FInputActionValue& Value)
{
	if (!GetController())
	{
		return;
	}

	FVector2D Input = Value.Get<FVector2D>();

	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

void ASRCharacter::OnStartJump(const FInputActionValue& Value)
{
	if (!GetController())
	{
		return;
	}

	bool Input = Value.Get<bool>();

	if (Input)
	{
		Jump();
	}
}

void ASRCharacter::OnStopJump(const FInputActionValue& Value)
{
	if (!GetController())
	{
		return;
	}

	bool Input = Value.Get<bool>();

	if (Input)
	{
		StopJumping();
	}
}

void ASRCharacter::UpdateCurrentHP(float Amount)
{
	CurrentHP = FMath::Clamp(CurrentHP + Amount, 0, MaxHP);

	if (ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetController()))
	{
		SRPlayerController->UpdateHUDHealth(CurrentHP / MaxHP);
	}

	if (CurrentHP == 0)
	{
		if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
		{
			SRGameInstance->OnGameOver();
		}
	}
}

float ASRCharacter::GetCurrentHP() const
{
	return CurrentHP;
}

float ASRCharacter::GetMaxHP() const
{
	return MaxHP;
}

