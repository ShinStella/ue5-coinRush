// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(int32 Level, int32 Wave, float Time, int32 Score, float HealthPercent);

	void SetHUDLevel(int32 Level);
	void SetHUDWave(int32 Wave);
	void SetHUDTime(float Time);
	void SetHUDScore(int32 Score);
	void SetHUDHealth(float HealthPercent);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreTextBlock;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};
