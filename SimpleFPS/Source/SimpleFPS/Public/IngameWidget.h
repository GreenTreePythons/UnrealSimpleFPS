// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleFPS/SimpleFPSWeaponComponent.h"
#include "IngameWidget.generated.h"

class ASimpleFPSCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBulletChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBulletDropped);

UCLASS()
class SIMPLEFPS_API UIngameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Begin Play alternative
	virtual void NativeConstruct() override;
	
public:

	// UFUNCTION(BlueprintCallable)
	// void UpdateBulletUI();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBulletChanged OnBulletChanged;

	UFUNCTION()
	void RefreshBulletCount();

	UFUNCTION()
	void OnDamaged();
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* TxtBulletCount;
	
	UFUNCTION(BlueprintPure)
	float CalculateHealthPercentage();

	UPROPERTY()
	ASimpleFPSCharacter* FPSCharacter;
	
	UPROPERTY()
	USimpleFPSWeaponComponent* WeaponComponent;

	UFUNCTION()
	void OnWeaponChanged(USimpleFPSWeaponComponent* NewWeapon);

	UFUNCTION()
	void OnDropWeapon();
};