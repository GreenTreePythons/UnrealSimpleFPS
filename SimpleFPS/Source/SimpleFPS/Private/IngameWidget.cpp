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
	TxtBulletCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtBulletCount")));
	FPSCharacter->OnWeaponAttached.AddDynamic(this, &UIngameWidget::OnWeaponChanged);
	FPSCharacter->OnWeaponDetached.AddDynamic(this, &UIngameWidget::OnDropWeapon);
	RefreshBulletCount();
}

void UIngameWidget::OnDropWeapon()
{
	WeaponComponent = nullptr;
	UE_LOG(LogTemp, Error, TEXT("OnDropWeapon ingame ui"));
	RefreshBulletCount();
}

void UIngameWidget::OnWeaponChanged(USimpleFPSWeaponComponent* NewWeapon)
{
	WeaponComponent = NewWeapon;
	UE_LOG(LogTemp, Error, TEXT("OnWeaponChanged ingame ui"));
	RefreshBulletCount();
}

float UIngameWidget::CalculateHealthPercentage()
{
	if (FPSCharacter == nullptr) return 0.0f;
	return FPSCharacter->GetHealth() / FPSCharacter->GetMaxHealth();
}

void UIngameWidget::RefreshBulletCount()
{
	if (!WeaponComponent) 
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponComponent is null"));
		TxtBulletCount->SetText(FText::FromString(TEXT("")));
		return;
	}

	int32 currentBulletCount = WeaponComponent->CurrentBulletCount;
	int32 maxBulletCount = WeaponComponent->MaxBulletCount;
	TxtBulletCount->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), currentBulletCount, maxBulletCount)));
}


void UIngameWidget::OnDamaged()
{
		
}
