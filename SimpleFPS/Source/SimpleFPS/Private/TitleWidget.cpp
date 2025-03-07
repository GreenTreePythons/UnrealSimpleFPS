// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleFPS/Public/TitleWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStartButton")));
	
	// Game Start 버튼을 찾고 클릭 시 이벤트 연결
	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnGameStartButtonClicked);
	}
}

void UTitleWidget::OnGameStartButtonClicked()
{
	// "FirstPersonMap"으로 레벨 전환
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonMap"));
}

