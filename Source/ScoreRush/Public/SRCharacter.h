// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class SCORERUSH_API ASRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRCharacter();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnMove(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnLook(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnStartJump(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnStopJump(const FInputActionValue& Value);

	void UpdateCurrentHP(float Amount);
	
	float GetCurrentHP() const;
	float GetMaxHP() const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float CurrentHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float MaxHP;
};
