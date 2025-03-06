// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleGameMode::ATitleGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetClass(TEXT("/Game/UI/WBP_Title"));
	if (TitleWidgetClass.Succeeded())
	{
		UUserWidget* TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass.Class);

		if (TitleWidget)
		{
			TitleWidget->AddToViewport();
		}
	}
}

void ATitleGameMode::BeginPlay()
{
	
}