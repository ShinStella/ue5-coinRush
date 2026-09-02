// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelStruct.generated.h"

USTRUCT(BlueprintType)
struct FWaveItem
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemID = "Default";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Probability = 0.0f;
};

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 WaveIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WaveTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SpawnItemCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWaveItem> WaveItems;
};

USTRUCT(BlueprintType)
struct FLevelStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWaveStruct> Waves;
};