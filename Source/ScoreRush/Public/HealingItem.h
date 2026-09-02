// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API AHealingItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void UseItem();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Healing")
	int32 Value;
};
