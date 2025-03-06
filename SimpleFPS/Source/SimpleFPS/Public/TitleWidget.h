// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFPS_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnStartButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	virtual void NativeConstruct() override;
};
