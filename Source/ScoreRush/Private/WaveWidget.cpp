// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveWidget.h"

void UWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FWidgetAnimationDynamicEvent Event;
	Event.BindUFunction(this, FName("OnWaveAnimationFinished"));

	BindToAnimationFinished(WaveAnimation, Event);
}

void UWaveWidget::OnWaveAnimationFinished()
{
	if (OnEndWaveAnim.IsBound())
	{
		OnEndWaveAnim.Broadcast();
	}
}

void UWaveWidget::InitWidget(int32 Wave)
{
	SetWave(Wave);
	PlayAnimation(WaveAnimation);
}

void UWaveWidget::SetWave(int32 Wave)
{
	if (WaveTextBlock)
	{
		WaveTextBlock->SetText(FText::FromString(FString::FromInt(Wave)));
	}
}
