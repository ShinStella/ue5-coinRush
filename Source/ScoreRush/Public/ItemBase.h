// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ItemBase.generated.h"

UCLASS()
class SCORERUSH_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

public:
	virtual void UseItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnOverlapped(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	USceneComponent* SceneCompoent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	USoundBase* ItemSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UParticleSystem* ItemEffect;
};
