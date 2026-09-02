// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuWidget.h"
#include "HUDWidget.h"
#include "ClearWidget.h"
#include "GameOverWidget.h"
#include "LevelWidget.h"
#include "WaveWidget.h"
#include "HealthBar3DWidget.h"
#include "Item3DWidget.h"
#include "ItemInfoWidget.h"
#include "SRPlayerController.generated.h"

class USRGameInstance;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class SCORERUSH_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASRPlayerController();

	virtual void BeginPlay() override;

	void HideAllWidget();

	void ShowMainMenuWidget();
	void HideMainMenuWidget();

	void ShowLevelWidget(int32 Level);
	void HideLevelWidget();

	void ShowWaveWidget(int32 Wave);
	void HideWaveWidget();

	void ShowHUDWidget(int32 Level, int32 Wave, float Time, int32 Score, float HealthPercent);
	void UpdateHUDWave(int32 Wave);
	void UpdateHUDTime(float Time);
	void UpdateHUDScore(int32 Score);
	void UpdateHUDHealth(float HealthPercent);
	void HideHUDWidget();

	void ShowClearWidget(int32 Score);
	void HideClearWidget();

	void ShowGameOverWidget();
	void HideGameOverWidget();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpInput;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ULevelWidget> LevelWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	ULevelWidget* LevelWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UWaveWidget> WaveWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWaveWidget* WaveWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UHUDWidget* HUDWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UClearWidget> ClearWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UClearWidget* ClearWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UGameOverWidget* GameOverWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UHealthBar3DWidget> HealthBar3DWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UHealthBar3DWidget* HealthBar3DWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItem3DWidget> Item3DWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UItem3DWidget* Item3DWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItemInfoWidget> ItemInfoWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UItemInfoWidget* ItemInfoWidget;

private:
	USRGameInstance* SRGameInstance;
};
