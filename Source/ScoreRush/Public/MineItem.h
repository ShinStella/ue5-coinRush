// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API AMineItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	AMineItem();

	virtual void UseItem();
	virtual void OnOverlapped(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	float ExplosionTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	float ExplosionRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mine")
	int32 Damage;

private:
	bool IsWorking;
	FTimerHandle ExplosionTimer;
};
