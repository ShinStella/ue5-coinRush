// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SRCharacter.h"

AItemBase::AItemBase() :
	SceneCompoent(nullptr),
	StaticMeshComponent(nullptr),
	SphereCollision(nullptr),
	ItemSound(nullptr),
	ItemEffect(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	SceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneCompoent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(StaticMeshComponent);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapped);
}

void AItemBase::UseItem()
{

}

void AItemBase::OnOverlapped(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ASRCharacter::StaticClass()))
	{
		if (ItemSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ItemSound, GetActorLocation());
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
					2.0f,
					false);
			}
		}

		UseItem();
	}
}
