// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWidget.h"

void ULevelWidget::NativeConstruct()
{
    Super::NativeConstruct();

    FWidgetAnimationDynamicEvent Event;
    Event.BindUFunction(this, FName("OnLevelAnimationFinished"));

    BindToAnimationFinished(LevelAnimation, Event);
}

void ULevelWidget::OnLevelAnimationFinished()
{
	if (OnEndLevelAnim.IsBound())
	{
		OnEndLevelAnim.Broadcast();
	}
}

void ULevelWidget::InitWidget(int32 Level)
{
	SetLevel(Level);
	PlayAnimation(LevelAnimation);
}

void ULevelWidget::SetLevel(int32 Level)
{
	if (LevelTextBlock)
	{
		LevelTextBlock->SetText(FText::FromString(FString::FromInt(Level)));
	}
}