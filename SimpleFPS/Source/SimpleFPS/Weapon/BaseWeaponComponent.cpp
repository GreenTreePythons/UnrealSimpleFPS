// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeaponComponent.h"

#include "SimpleFPS/Character/FPSCharacter.h"

UBaseWeaponComponent::UBaseWeaponComponent()
{
	WeaponData.Damage = 20.0f;
	WeaponData.FireRate = 0.1f;
	WeaponData.AmmoCapacity = 30;
	WeaponData.WeaponName = "Default";
	WeaponData.CollisionRadius = 100.0f;

	Character = nullptr;
}

void UBaseWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseWeaponComponent::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("%s fired! Damage: %f"), *WeaponData.WeaponName, WeaponData.Damage);
}

void UBaseWeaponComponent::PickupWeapon(class AFPSCharacter* NewOwner)
{
	if (!NewOwner) return;

	Character = NewOwner;
	
	SetSimulatePhysics(false);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));

		
	// Character->SetCurrentWeapon(this);
}

void UBaseWeaponComponent::DropWeapon()
{
	
}

const FWeaponData& UBaseWeaponComponent::GetWeaponData() const
{
	return WeaponData;
}
