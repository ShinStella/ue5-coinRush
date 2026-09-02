// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "SRCharacter.h"

void AHealingItem::UseItem()
{
	if (ASRCharacter* SRCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<ASRCharacter>())
	{
		SRCharacter->UpdateCurrentHP(Value);
	}

	Destroy();
}
