// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Delegates.h"
#include "LevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCORERUSH_API ULevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void OnLevelAnimationFinished();

	void InitWidget(int32 Level);
	void SetLevel(int32 Level);

public:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> LevelAnimation;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextBlock;

public:
	FOnEndLevelAnim OnEndLevelAnim;
};
