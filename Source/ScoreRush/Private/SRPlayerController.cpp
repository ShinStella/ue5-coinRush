// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "SRGameInstance.h"
#include "SRGameState.h"
#include "EnumDatas.h"

ASRPlayerController::ASRPlayerController()
{
	SRGameInstance = GetGameInstance<USRGameInstance>();
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (SRGameInstance)
	{
		if (SRGameInstance->GetSRGameState() == EGameState::START)
		{
			ShowMainMenuWidget();
		}
		else
		{
			SRGameInstance->OnStartGame();
		}
	}
}

void ASRPlayerController::HideAllWidget()
{
	HideMainMenuWidget();
	HideHUDWidget();
	HideClearWidget();
	HideGameOverWidget();
	HideLevelWidget();
	HideWaveWidget();
}

void ASRPlayerController::ShowMainMenuWidget()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);

		MainMenuWidget->OnStartGame.AddUObject(this, &ASRPlayerController::HideMainMenuWidget);
		MainMenuWidget->OnExitGame.AddUObject(this, &ASRPlayerController::HideMainMenuWidget);

		if (SRGameInstance)
		{
			MainMenuWidget->OnStartGame.AddUObject(SRGameInstance, &USRGameInstance::OnStartGame);
			MainMenuWidget->OnExitGame.AddUObject(SRGameInstance, &USRGameInstance::OnExitGame);
		}

		MainMenuWidget->AddToViewport();

		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::HideMainMenuWidget()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::ShowLevelWidget(int32 Level)
{
	if (LevelWidget)
	{
		LevelWidget->RemoveFromParent();
		LevelWidget = nullptr;
	}

	if (LevelWidgetClass)
	{
		LevelWidget = CreateWidget<ULevelWidget>(GetWorld(), LevelWidgetClass);
		LevelWidget->InitWidget(Level);
		LevelWidget->OnEndLevelAnim.AddUObject(this, &ASRPlayerController::HideLevelWidget);

		if (ASRGameState* SRGameState = GetWorld()->GetGameState<ASRGameState>())
		{
			LevelWidget->OnEndLevelAnim.AddUObject(SRGameState, &ASRGameState::BeforeStartWave);
		}

		LevelWidget->AddToViewport();

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::HideLevelWidget()
{
	if (LevelWidget)
	{
		LevelWidget->RemoveFromParent();
		LevelWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::ShowWaveWidget(int32 Wave)
{
	if (WaveWidget)
	{
		WaveWidget->RemoveFromParent();
		WaveWidget = nullptr;
	}

	if (WaveWidgetClass)
	{
		WaveWidget = CreateWidget<UWaveWidget>(GetWorld(), WaveWidgetClass);
		WaveWidget->InitWidget(Wave);
		WaveWidget->OnEndWaveAnim.AddUObject(this, &ASRPlayerController::HideWaveWidget);

		if (ASRGameState* SRGameState = GetWorld()->GetGameState<ASRGameState>())
		{
			WaveWidget->OnEndWaveAnim.AddUObject(SRGameState, &ASRGameState::StartWave);
		}

		WaveWidget->AddToViewport();

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::HideWaveWidget()
{
	if (WaveWidget)
	{
		WaveWidget->RemoveFromParent();
		WaveWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::ShowHUDWidget(int32 Level, int32 Wave, float Time, int32 Score, float HealthPercent)
{
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
		HUDWidget = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->InitWidget(Level, Wave, Time, Score, HealthPercent);
		HUDWidget->AddToViewport();

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::UpdateHUDWave(int32 Wave)
{
	if (HUDWidget)
	{
		HUDWidget->SetHUDWave(Wave);
	}
}

void ASRPlayerController::UpdateHUDTime(float Time)
{
	if (HUDWidget)
	{
		HUDWidget->SetHUDTime(Time);
	}
}

void ASRPlayerController::UpdateHUDScore(int32 Score)
{
	if (HUDWidget)
	{
		HUDWidget->SetHUDScore(Score);
	}
}

void ASRPlayerController::UpdateHUDHealth(float HealthPercent)
{
	if (HUDWidget)
	{
		HUDWidget->SetHUDHealth(HealthPercent);
	}
}

void ASRPlayerController::HideHUDWidget()
{
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
		HUDWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::ShowClearWidget(int32 Score)
{
	if (ClearWidget)
	{
		ClearWidget->RemoveFromParent();
		ClearWidget = nullptr;
	}

	if (ClearWidgetClass)
	{
		ClearWidget = CreateWidget<UClearWidget>(GetWorld(), ClearWidgetClass);
		ClearWidget->InitWidget(Score);

		ClearWidget->OnRestartGame.AddUObject(this, &ASRPlayerController::HideAllWidget);
		ClearWidget->OnReturnToMainMenu.AddUObject(this, &ASRPlayerController::HideAllWidget);

		if (SRGameInstance)
		{
			ClearWidget->OnRestartGame.AddUObject(SRGameInstance, &USRGameInstance::OnRestartGame);
			ClearWidget->OnReturnToMainMenu.AddUObject(SRGameInstance, &USRGameInstance::InitGame);
		}

		ClearWidget->AddToViewport();

		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::HideClearWidget()
{
	if (ClearWidget)
	{
		ClearWidget->RemoveFromParent();
		ClearWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ASRPlayerController::ShowGameOverWidget()
{
	if (GameOverWidget)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget = nullptr;
	}

	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);

		GameOverWidget->OnRestartGame.AddUObject(this, &ASRPlayerController::HideAllWidget);
		GameOverWidget->OnReturnToMainMenu.AddUObject(this, &ASRPlayerController::HideAllWidget);

		if (SRGameInstance)
		{
			GameOverWidget->OnRestartGame.AddUObject(SRGameInstance, &USRGameInstance::OnRestartGame);
			GameOverWidget->OnReturnToMainMenu.AddUObject(SRGameInstance, &USRGameInstance::InitGame);
		}

		GameOverWidget->AddToViewport();

		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::HideGameOverWidget()
{
	if (GameOverWidget)
	{
		GameOverWidget->RemoveFromParent();
		GameOverWidget = nullptr;

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}
