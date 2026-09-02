// Fill out your copyright notice in the Description page of Project Settings.


#include "SRGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SRGameState.h"
#include "SRPlayerController.h"

USRGameInstance::USRGameInstance() :
	ItemDataTable(nullptr),
	LevelDataTable(nullptr),
	SRCurrentHP(100),
	SRMaxHp(100),
	GameState(EGameState::START),
	SRTotalScore(0),
	SRLevelIndex(0)
{
	Levels.Empty();
	Levels.Push(FName(TEXT("Easy")));
	Levels.Push(FName(TEXT("Normal")));
	Levels.Push(FName(TEXT("Hard")));

	SRLevelCount = Levels.Num();

	ItemMap.Empty();
	LevelMap.Empty();

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemFinder(
		TEXT("/Script/Engine.DataTable'/Game/Blueprints/ItemDataTable.ItemDataTable'")
	);

	if (ItemFinder.Succeeded())
	{
		ItemDataTable = ItemFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> LevelFinder(
		TEXT("/Script/Engine.DataTable'/Game/Blueprints/LevelDataTable.LevelDataTable'")
	);

	if (LevelFinder.Succeeded())
	{
		LevelDataTable = LevelFinder.Object;
	}

	LoadItemDataTable();
	LoadLevelDataTable();

	OpenSRLevel();
}

void USRGameInstance::LoadItemDataTable()
{
	if (!ItemDataTable)
	{
		return;
	}

	TArray<FItemStruct*> AllRows{};
	ItemDataTable->GetAllRows(TEXT("Get All Item Rows"), AllRows);

	for (const FItemStruct* Row : AllRows)
	{
		if (Row)
		{
			ItemMap.Emplace(Row->ItemID, *Row);
		}
	}
}

void USRGameInstance::LoadLevelDataTable()
{
	if (!LevelDataTable)
	{
		return;
	}

	TArray<FLevelStruct*> AllRows{};
	LevelDataTable->GetAllRows(TEXT("Get All Level Rows"), AllRows);

	for (const FLevelStruct* Row : AllRows)
	{
		if (Row)
		{
			LevelMap.Emplace(Row->LevelIndex, *Row);
		}
	}
}

void USRGameInstance::GetItemData(FName ItemID, FItemStruct& ItemStruct)
{
	if (ItemMap.Contains(ItemID))
	{
		ItemStruct = ItemMap[ItemID];
	}
}

void USRGameInstance::GetWaveDatas(int32 LevelIndex, TArray<FWaveStruct>& WaveStructs)
{
	if (LevelMap.Contains(LevelIndex))
	{
		WaveStructs = LevelMap[LevelIndex].Waves;
	}
}

void USRGameInstance::InitGame()
{
	SRCurrentHP = 100;
	SRMaxHp = 100;
	GameState = EGameState::START;
	SRTotalScore = 0;
	SRLevelIndex = 0;

	OpenSRLevel();
}

void USRGameInstance::OnStartGame()
{
	SetGamePause(true);

	GameState = EGameState::PLAYING;

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->ShowLevelWidget(SRLevelIndex + 1);

		if (SRLevelIndex < SRLevelCount)
		{
			SRPlayerController->ShowHUDWidget(SRLevelIndex + 1, 1, LevelMap[SRLevelIndex].Waves[0].WaveTime, SRTotalScore, SRCurrentHP / SRMaxHp);
		}
	}
}

void USRGameInstance::OnRestartGame()
{
	SRCurrentHP = 100;
	SRMaxHp = 100;
	GameState = EGameState::PLAYING;
	SRTotalScore = 0;
	SRLevelIndex = 0;
	
	OpenSRLevel();
	OnStartGame();
}

void USRGameInstance::OpenSRLevel()
{
	if (GetWorld() && SRLevelIndex < SRLevelCount)
	{
		UGameplayStatics::OpenLevel(GetWorld(), Levels[SRLevelIndex]);
	}
}

void USRGameInstance::OnLevelClear(int32 newScore, float newCurrentHP)
{
	SRTotalScore = newScore;
	SRCurrentHP = newCurrentHP;
	SRLevelIndex += 1;

	if (SRLevelIndex == SRLevelCount)
	{
		OnGameClear();
	}
	else
	{
		OpenSRLevel();
	}
}

void USRGameInstance::OnGameOver()
{
	SetGamePause(true);

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->ShowGameOverWidget();
	}
}

void USRGameInstance::OnGameClear()
{
	SetGamePause(true);

	if (ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>())
	{
		SRPlayerController->ShowClearWidget(SRTotalScore);
	}
}

void USRGameInstance::OnExitGame()
{
	if (GetWorld())
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController<ASRPlayerController>(), EQuitPreference::Quit, false);
	}
}

void USRGameInstance::SetGamePause(bool IsPause)
{
	ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>();
	ASRGameState* SRGameState = GetWorld()->GetGameState<ASRGameState>();

	if (!SRPlayerController || !SRGameState)
	{
		return;
	}

	if (IsPause)
	{
		SRPlayerController->SetIgnoreMoveInput(true);
		SRPlayerController->SetIgnoreLookInput(true);
		SRGameState->PauseTime();
	}
	else
	{
		SRPlayerController->ResetIgnoreMoveInput();
		SRPlayerController->ResetIgnoreLookInput();
		SRGameState->ResumeTime();
	}
}

void USRGameInstance::SetSRTotalScore(int32 newScore)
{
	SRTotalScore = newScore;
}

void USRGameInstance::SetSRLevelIndex(int32 LevelIndex)
{
	SRLevelIndex = LevelIndex;
}

void USRGameInstance::SetSRCurrentHP(float CurrentHP)
{
	SRCurrentHP = CurrentHP;
}

EGameState USRGameInstance::GetSRGameState() const
{
	return GameState;
}

int32 USRGameInstance::GetSRTotalScore() const
{
	return SRTotalScore;
}

int32 USRGameInstance::GetSRLevelIndex() const
{
	return SRLevelIndex;
}

int32 USRGameInstance::GetSRLevelCount() const
{
	return SRLevelCount;
}

float USRGameInstance::GetSRCurrentHP() const
{
	return SRCurrentHP;
}

float USRGameInstance::GetSRMaxHP() const
{
	return SRMaxHp;
}
