// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SRCharacter.h"

AMineItem::AMineItem() :
	ExplosionCollision(nullptr),
	ExplosionSound(nullptr),
	ExplosionEffect(nullptr),
	ExplosionTime(3.0f),
	ExplosionRange(500.0f),
	Damage(30.0f),
	IsWorking(false)
{
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->SetupAttachment(StaticMeshComponent);

	ExplosionCollision->SetSphereRadius(ExplosionRange);
}

void AMineItem::UseItem()
{
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	if (ExplosionEffect)
	{
		TWeakObjectPtr<UParticleSystemComponent> Effect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

		if (Effect.IsValid())
		{
			FTimerHandle DestroyEffectTimer;

			GetWorldTimerManager().SetTimer(DestroyEffectTimer, [Effect]() {
				if (Effect.IsValid())
				{
					Effect->DestroyComponent();
				}
				},
				2.0f,
				false);
		}
	}

	TArray<AActor*> OverlappingActors{};
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor && OverlappingActor->IsA(ASRCharacter::StaticClass()))
		{
			if (ASRCharacter* SRCharacter = Cast<ASRCharacter>(OverlappingActor))
			{
				SRCharacter->UpdateCurrentHP(Damage * (-1));
			}
		}
	}

	Destroy();
}

void AMineItem::OnOverlapped(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ASRCharacter::StaticClass()) && !IsWorking)
	{
		IsWorking = true;

		if (ItemSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ItemSound, GetActorLocation());
		}

		if (ItemEffect)
		{
			TWeakObjectPtr<UParticleSystemComponent> Effect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ItemEffect, GetActorLocation());

			if (Effect.IsValid())
			{
				FTimerHandle DestroyEffectTimer;

				GetWorldTimerManager().SetTimer(DestroyEffectTimer, [Effect]() {
					if (Effect.IsValid())
					{
						Effect->DestroyComponent();
					}
					},
					ExplosionTime,
					false);
			}
		}

		GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AMineItem::UseItem, ExplosionTime, false);
	}
}
