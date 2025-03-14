// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleFPS/Public/TitleWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	// Game Start 버튼을 찾고 클릭 시 이벤트 연결
	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStartButton")));
	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnGameStartButtonClicked);
	}

	GameQuitButton = Cast<UButton>(GetWidgetFromName(TEXT("GameQuitButton")));
	if (GameQuitButton)
	{
		GameQuitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnGameQuitButtonClicked);
	}
}

void UTitleWidget::OnGameStartButtonClicked()
{
	// "FirstPersonMap"으로 레벨 전환
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonMap"));
}

void UTitleWidget::OnGameJoinButtonClicked()
{
	
}

void UTitleWidget::OnGameQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
