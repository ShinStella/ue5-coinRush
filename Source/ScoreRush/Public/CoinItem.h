// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "CoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API ACoinItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void UseItem();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Coin")
	int32 Point;
};
