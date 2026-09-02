// Fill out your copyright notice in the Description page of Project Settings.


#include "SRGameMode.h"
#include "SRGameState.h"
#include "SRPlayerController.h" 
#include "SRCharacter.h"

ASRGameMode::ASRGameMode()
{
	GameStateClass = ASRGameState::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	DefaultPawnClass = ASRCharacter::StaticClass();
}
