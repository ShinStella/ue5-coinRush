// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Delegates.h"
#include "WaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API UWaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void OnWaveAnimationFinished();

	void InitWidget(int32 Wave);
	void SetWave(int32 Wave);

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> WaveAnimation;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveTextBlock;

public:
	FOnEndWaveAnim OnEndWaveAnim;
};
