// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::InitWidget(int32 Level, int32 Wave, float Time, int32 Score, float HealthPercent)
{
	SetHUDLevel(Level);
	SetHUDWave(Wave);
	SetHUDTime(Time);
	SetHUDScore(Score);
	SetHUDHealth(HealthPercent);
}

void UHUDWidget::SetHUDLevel(int32 Level)
{
	if (LevelTextBlock)
	{
		LevelTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Level %d"), Level)));
	}
}

void UHUDWidget::SetHUDWave(int32 Wave)
{
	if (WaveTextBlock)
	{
		WaveTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Wave %d"), Wave)));
	}
}

void UHUDWidget::SetHUDTime(float Time)
{
	if (TimeTextBlock)
	{
		float HUDTime = FMath::Max(0.0f, Time);
		TimeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%0.1f"), HUDTime)));
	}
}

void UHUDWidget::SetHUDScore(int32 Score)
{
	if (ScoreTextBlock)
	{
		ScoreTextBlock->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

void UHUDWidget::SetHUDHealth(float HealthPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}
}
