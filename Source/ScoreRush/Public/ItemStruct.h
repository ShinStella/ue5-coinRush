// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnumDatas.h"
#include "ItemStruct.generated.h"

class AItemBase;

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemID = "Default";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType = EItemType::COIN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AItemBase> ItemClass;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;*/

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName = "Default";*/

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ItemDescription = "Default";*/
};