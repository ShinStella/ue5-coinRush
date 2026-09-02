// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "SRGameState.h"

void ACoinItem::UseItem()
{
	if (ASRGameState* SRGameState = GetWorld()->GetGameState<ASRGameState>())
	{
		SRGameState->AddScore(Point);
	}

	Destroy();
}
