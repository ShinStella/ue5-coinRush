// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Main Menu Widget
DECLARE_MULTICAST_DELEGATE(FOnStartGame);
DECLARE_MULTICAST_DELEGATE(FOnExitGame);

// Clear Widget, Game Over Widget
DECLARE_MULTICAST_DELEGATE(FOnRestartGame);
DECLARE_MULTICAST_DELEGATE(FOnReturnToMainMenu);

// Level Widget
DECLARE_MULTICAST_DELEGATE(FOnEndLevelAnim);

// Wave Widget
DECLARE_MULTICAST_DELEGATE(FOnEndWaveAnim);