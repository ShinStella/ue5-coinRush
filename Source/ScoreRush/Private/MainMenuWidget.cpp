// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
	}
}

void UMainMenuWidget::OnStartButtonClicked()
{
	if (OnStartGame.IsBound())
	{
		OnStartGame.Broadcast();
	}
}

void UMainMenuWidget::OnExitButtonClicked()
{
	if (OnExitGame.IsBound())
	{
		OnExitGame.Broadcast();
	}
}