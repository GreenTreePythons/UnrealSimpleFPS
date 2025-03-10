// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleFPS/SimpleFPSCharacter.h"

void UIngameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	FPSCharacter = Cast<ASimpleFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	WeaponComponent = Cast<USimpleFPSWeaponComponent>(GetWidgetFromName(TEXT("TxtBulletCount")));
}

float UIngameWidget::CalculateHealthPercentage()
{
	if (FPSCharacter == nullptr) return 0.0f;
	return FPSCharacter->GetHealth() / FPSCharacter->GetMaxHealth();
}

FText UIngameWidget::CalculateBulletCount()
{
	if (!WeaponComponent) 
	{
		return FText::FromString(TEXT("0/0"));
	}

	int32 currentBulletCount = WeaponComponent->CurrentBulletCount;
	int32 maxBulletCount = WeaponComponent->MaxBulletCount;

	if (maxBulletCount <= 0) 
	{
		return FText::FromString(TEXT("0/0"));
	}

	FText::FromString(FString::Printf(TEXT("%d/%d"), currentBulletCount, maxBulletCount));
}


void UIngameWidget::OnDamaged()
{
		
}
