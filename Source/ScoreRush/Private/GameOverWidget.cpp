// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "ClearWidget.h"

void UGameOverWidget::NativeConstruct()
{
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartButtonClicked);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnMainMenuButtonClicked);
	}
}

void UGameOverWidget::OnRestartButtonClicked()
{
	if (OnRestartGame.IsBound())
	{
		OnRestartGame.Broadcast();
	}
}

void UGameOverWidget::OnMainMenuButtonClicked()
{
	if (OnReturnToMainMenu.IsBound())
	{
		OnReturnToMainMenu.Broadcast();
	}
}
