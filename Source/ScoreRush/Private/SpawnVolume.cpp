// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "SRGameInstance.h"
#include "ItemBase.h"
#include "EnumDatas.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(BoxCollision);

	SpawnedItems.Empty();
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollision)
	{
		BoxExtent = BoxCollision->GetScaledBoxExtent();
	}
}

void ASpawnVolume::SpawnItems(int32 SpawnItemCount, const TArray<FWaveItem>& WaveItems)
{
	SpawnedItems.Empty();
	SpawnedItems.Reserve(SpawnItemCount);

	for (int i = 0; i < SpawnItemCount; i++)
	{
		float RandProb = FMath::RandRange(0.0f, 100.0f);
		float SumProb{};

		for (const FWaveItem& WaveItem : WaveItems)
		{
			SumProb += WaveItem.Probability;

			if (SumProb >= RandProb)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item ID : %s"), *WaveItem.ItemID.ToString());
				SpawnItem(WaveItem.ItemID);
				break;
			}
		}
	}
}

void ASpawnVolume::SpawnItem(FName ItemID)
{
	FVector SpawnLocation{};
	FVector Location = GetActorLocation();
	SpawnLocation.X = FMath::RandRange(Location.X - BoxExtent.X, Location.X + BoxExtent.X);
	SpawnLocation.Y = FMath::RandRange(Location.Y - BoxExtent.Y, Location.Y + BoxExtent.Y);
	SpawnLocation.Z = FMath::RandRange(Location.Z, Location.Z + BoxExtent.Z);

	if (USRGameInstance* SRGameInstance = GetGameInstance<USRGameInstance>())
	{
		FItemStruct ItemStruct{};
		SRGameInstance->GetItemData(ItemID, ItemStruct);

		if (ItemStruct.ItemType == EItemType::MINE)
		{
			SpawnLocation.Z = Location.Z - BoxExtent.Z;
		}

		AItemBase* Item = GetWorld()->SpawnActor<AItemBase>(ItemStruct.ItemClass, SpawnLocation, FRotator::ZeroRotator);
		if (Item)
		{
			SpawnedItems.Emplace(Item);
		}
	}
}

void ASpawnVolume::RemoveSpawnedItems()
{
	for (TWeakObjectPtr<AItemBase> Item : SpawnedItems)
	{
		if (Item.IsValid())
		{
			Item->Destroy();
		}
	}
}

