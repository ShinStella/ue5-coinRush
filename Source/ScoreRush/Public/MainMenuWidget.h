// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Delegates.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnStartButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnExitButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

public:
	FOnStartGame OnStartGame;
	FOnExitGame OnExitGame;
};
