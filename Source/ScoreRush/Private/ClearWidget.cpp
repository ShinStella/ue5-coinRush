// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWidget.h"

void UClearWidget::NativeConstruct()
{
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UClearWidget::OnRestartButtonClicked);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UClearWidget::OnMainMenuButtonClicked);
	}
}

void UClearWidget::InitWidget(int32 Score)
{
	SetScore(Score);
}

void UClearWidget::OnRestartButtonClicked()
{
	if (OnRestartGame.IsBound())
	{
		OnRestartGame.Broadcast();
	}
}

void UClearWidget::OnMainMenuButtonClicked()
{
	if (OnReturnToMainMenu.IsBound())
	{
		OnReturnToMainMenu.Broadcast();
	}
}

void UClearWidget::SetScore(int32 Score)
{
	if (ScoreTextBlock)
	{
		ScoreTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Total Score : %d"), Score)));
	}
}