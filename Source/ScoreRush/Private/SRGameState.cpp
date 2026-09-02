// Fill out your copyright notice in the Description page of Project Settings.


#include "SRGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SRGameInstance.h"
#include "SRPlayerController.h"
#include "SRCharacter.h"
#include "SpawnVolume.h"

ASRGameState::ASRGameState() :
	WaveIndex(0),
	SpawnVolume(nullptr)
{
	Waves.Empty();

	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		Score = SRGameInstance->GetSRTotalScore();
		LevelIndex = SRGameInstance->GetSRLevelIndex();
		SRGameInstance->GetWaveDatas(LevelIndex, Waves);
	}

	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> SpawnVolumes{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), SpawnVolumes);

	if (!SpawnVolumes.IsEmpty())
	{
		SpawnVolume = MakeWeakObjectPtr<ASpawnVolume>(Cast<ASpawnVolume>(SpawnVolumes[0]));
	}
}

void ASRGameState::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().ClearTimer(WaveTimer);
	GetWorldTimerManager().ClearTimer(HUDUpdateTimer);
}

void ASRGameState::AddScore(int32 Amount)
{
	Score += Amount;

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->UpdateHUDScore(Score);
	}
}

void ASRGameState::UpdateHUDTime()
{
	if (!GetWorld())
	{
		return;
	}

	float LeftTime = GetWorldTimerManager().GetTimerRemaining(WaveTimer);

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->UpdateHUDTime(LeftTime);
	}
}

void ASRGameState::BeforeStartWave()
{
	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		SRGameInstance->SetGamePause(true);

		if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
		{
			SRPlayerController->ShowWaveWidget(WaveIndex + 1);
		}
	}
}

void ASRGameState::StartWave()
{
	if (WaveIndex >= Waves.Num())
	{
		return;
	}

	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		SRGameInstance->SetGamePause(false);
	}

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->UpdateHUDWave(WaveIndex + 1);
	}

	GetWorldTimerManager().SetTimer(WaveTimer, this, &ASRGameState::EndWave, Waves[WaveIndex].WaveTime, false);
	GetWorldTimerManager().SetTimer(HUDUpdateTimer, this, &ASRGameState::UpdateHUDTime, 0.05f, true);

	int32 SpawnItemCount = Waves[WaveIndex].SpawnItemCount;
	TArray<FWaveItem> WaveItems = Waves[WaveIndex].WaveItems;

	if (SpawnVolume.IsValid())
	{
		SpawnVolume->SpawnItems(SpawnItemCount, WaveItems);
	}
}

void ASRGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimer);
	GetWorldTimerManager().ClearTimer(HUDUpdateTimer);

	if (SpawnVolume.IsValid())
	{
		SpawnVolume->RemoveSpawnedItems();
	}

	WaveIndex += 1;

	if (WaveIndex < Waves.Num())
	{
		BeforeStartWave();
	}
	else
	{
		ClearLevel();
	}
}

void ASRGameState::ClearLevel()
{
	USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>();
	ASRCharacter* SRCharacter = GetWorld()->GetFirstPlayerController<ASRPlayerController>()->GetPawn<ASRCharacter>();

	if (SRGameInstance && SRCharacter)
	{
		SRGameInstance->OnLevelClear(Score, SRCharacter->GetCurrentHP());
	}

	EndLevel();
}

void ASRGameState::ClearGame()
{
	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->ShowClearWidget(Score);
	}
}

void ASRGameState::GameOver()
{
	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		SRGameInstance->OnGameOver();
	}

	EndLevel();
}

void ASRGameState::EndLevel()
{
	Destroy();
}

void ASRGameState::PauseTime()
{
	if (GetWorldTimerManager().IsTimerActive(WaveTimer))
	{
		GetWorldTimerManager().PauseTimer(WaveTimer);
	}

	if (GetWorldTimerManager().IsTimerActive(HUDUpdateTimer))
	{
		GetWorldTimerManager().PauseTimer(HUDUpdateTimer);
	}
}

void ASRGameState::ResumeTime()
{
	if (GetWorldTimerManager().IsTimerPaused(WaveTimer))
	{
		GetWorldTimerManager().UnPauseTimer(WaveTimer);
	}

	if (GetWorldTimerManager().IsTimerPaused(HUDUpdateTimer))
	{
		GetWorldTimerManager().UnPauseTimer(HUDUpdateTimer);
	}
}
