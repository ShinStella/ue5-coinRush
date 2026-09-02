// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LevelStruct.h"
#include "SRGameState.generated.h"

class ASpawnVolume;
/**
 * 
 */
UCLASS()
class SCORERUSH_API ASRGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ASRGameState();

	virtual void BeginPlay() override;
	void AddScore(int32 Amount);
	void UpdateHUDTime();
	void BeforeStartWave();
	void StartWave();
	void EndWave();
	void ClearLevel();
	void ClearGame();
	void GameOver();
	void EndLevel();
	void PauseTime();
	void ResumeTime();

private:
	int32 Score;
	int32 WaveIndex;
	int32 LevelIndex;

	TWeakObjectPtr<ASpawnVolume> SpawnVolume;
	TArray<FWaveStruct> Waves;

	FTimerHandle WaveTimer;
	FTimerHandle HUDUpdateTimer;
};
