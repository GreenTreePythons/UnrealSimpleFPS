// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeaponComponent.h"
#include "SimpleFPS/Character/FPSCharacter.h"

UBaseWeaponComponent::UBaseWeaponComponent()
{
	WeaponData.Damage = 20.0f;
	WeaponData.FireRate = 0.1f;
	WeaponData.AmmoCapacity = 30;
	WeaponData.WeaponName = "Default";

	OnComponentBeginOverlap.AddDynamic(this, &UBaseWeaponComponent::OnWeaponBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UBaseWeaponComponent::OnWeaponEndOverlap);

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

void UBaseWeaponComponent::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
												bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetNearbyWeapon(this);
	}
}

void UBaseWeaponComponent::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetNearbyWeapon(nullptr);
	}
}

const FWeaponData& UBaseWeaponComponent::GetWeaponData() const
{
	return WeaponData;
}
