// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

UCLASS()
class SIMPLEFPS_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta = (BindWidget))
	class UButton* GameStartButton;  // 게임 시작 버튼

	UPROPERTY(Meta = (BindWidget))
	class UButton* GameJoinButton;

	UPROPERTY(Meta=(BindWidget))
	class UButton* GameQuitButton;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnGameStartButtonClicked();

	UFUNCTION()
	void OnGameJoinButtonClicked();

	UFUNCTION()
	void OnGameQuitButtonClicked();
};
