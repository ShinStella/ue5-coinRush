// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Delegates.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnRestartButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnMainMenuButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

public:
	FOnRestartGame OnRestartGame;
	FOnReturnToMainMenu OnReturnToMainMenu;
};
