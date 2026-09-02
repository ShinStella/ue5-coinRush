// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ItemStruct.h"
#include "LevelStruct.h"
#include "EnumDatas.h"
#include "SRGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SCORERUSH_API USRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USRGameInstance();

	void LoadItemDataTable();
	void LoadLevelDataTable();

	void GetItemData(FName ItemID, FItemStruct& ItemStruct);
	void GetWaveDatas(int32 LevelIndex, TArray<FWaveStruct>& WaveStructs);

	void InitGame();
	void OnStartGame();
	void OnRestartGame();
	void OpenSRLevel(); 
	void OnLevelClear(int32 newScore, float newCurrentHP);
	void OnGameOver();
	void OnGameClear();
	void OnExitGame();
	
	void SetGamePause(bool IsPause);
	void SetSRTotalScore(int32 newScore);
	void SetSRLevelIndex(int32 LevelIndex);
	void SetSRCurrentHP(float CurrentHP);

	EGameState GetSRGameState() const;
	int32 GetSRTotalScore() const;
	int32 GetSRLevelIndex() const;
	int32 GetSRLevelCount() const;
	float GetSRCurrentHP() const;
	float GetSRMaxHP() const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* ItemDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* LevelDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TArray<FName> Levels;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	float SRCurrentHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	float SRMaxHp;

private:
	EGameState GameState;
	int32 SRTotalScore;
	int32 SRLevelIndex;
	int32 SRLevelCount;

	TMap<FName, FItemStruct> ItemMap;
	TMap<int32, FLevelStruct> LevelMap;
};
