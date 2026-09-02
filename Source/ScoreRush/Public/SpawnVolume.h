// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LevelStruct.h"
#include "SpawnVolume.generated.h"

class AItemBase;

UCLASS()
class SCORERUSH_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

	virtual void BeginPlay() override;

	void SpawnItems(int32 SpawnItemCount, const TArray<FWaveItem>& WaveItems);
	void SpawnItem(FName ItemID);
	void RemoveSpawnedItems();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnVolume")
	UBoxComponent* BoxCollision;

private:
	FVector BoxExtent;
	TArray<TWeakObjectPtr<AItemBase>> SpawnedItems;
};
