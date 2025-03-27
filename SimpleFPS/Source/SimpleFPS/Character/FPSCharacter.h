// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

struct FWeaponData;
class UBaseWeaponComponent;
class UIngameWidget;

#include "FPSCharacter.generated.h"

UCLASS()
class SIMPLEFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EquipWeapon(UBaseWeaponComponent* NewWeapon);
	void SetNearbyWeapon(UBaseWeaponComponent* Weapon);
	UBaseWeaponComponent* GetNearbyWeapon();
	const FWeaponData* GetWeaponData();
	
private:
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category=Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category=Input)
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category=Input)
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category=Input)
	class UInputAction* PickupWeaponAction;
	
	UPROPERTY(EditAnywhere, Category=Input)
	class UInputAction* DropWeaponAction;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	bool bIsDashing;
	float DashSpeed;
	float DefaultSpeed;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void PickupWeapon();
	void DropWeapon();
	void StartDash();
	void StopDash();
	void Shoot();
	
	UBaseWeaponComponent* EquipedWeapon;
	UBaseWeaponComponent* NearbyWeapon;
	UIngameWidget* IngameWidget;
};
