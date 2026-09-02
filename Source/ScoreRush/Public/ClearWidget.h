// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Delegates.h"
#include "ClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void InitWidget(int32 Score);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnRestartButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnMainMenuButtonClicked();

	void SetScore(int32 Score);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

public:
	FOnRestartGame OnRestartGame;
	FOnReturnToMainMenu OnReturnToMainMenu;
};
