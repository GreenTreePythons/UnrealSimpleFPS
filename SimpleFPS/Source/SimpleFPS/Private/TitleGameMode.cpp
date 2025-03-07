// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "TitleWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_Title(TEXT("/Game/UMG/WBP_Title.WBP_Title_C"));
	if (WBP_Title.Succeeded())
	{
		TitleWidgetClass = WBP_Title.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WBP_Title null"));
	}
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(TitleWidgetClass))
	{
		TitleWidget = Cast<UTitleWidget>(CreateWidget(GetWorld(), TitleWidgetClass));
		if (IsValid((TitleWidget)))
		{
			TitleWidget->AddToViewport();
		}
	}
}