// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EGameState : uint8
{
	START,
	PLAYING,
	END,
};

UENUM()
enum class EItemType : uint8
{
	COIN,
	MINE,
	HEALING,
	DEBUFF,
};