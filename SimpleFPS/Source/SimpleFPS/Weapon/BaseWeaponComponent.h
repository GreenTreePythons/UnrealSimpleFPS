// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"

class AFPSCharacter;

#include "BaseWeaponComponent.generated.h"

USTRUCT()
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY()
	float Damage;

	UPROPERTY()
	float FireRate;

	UPROPERTY()
	int32 AmmoCapacity;

	UPROPERTY()
	FString WeaponName;
};

UCLASS()
class SIMPLEFPS_API UBaseWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UBaseWeaponComponent();

	const FWeaponData& GetWeaponData() const;

	AFPSCharacter* Character;

	virtual void Fire();
	virtual void PickupWeapon(class AFPSCharacter* NewOwner);
	virtual void DropWeapon();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	FWeaponData WeaponData;

	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							  bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
