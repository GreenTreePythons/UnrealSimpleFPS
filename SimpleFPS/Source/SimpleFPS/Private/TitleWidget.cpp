// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartButtonClicked);
	}
}

void UTitleWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainLevel"));
}