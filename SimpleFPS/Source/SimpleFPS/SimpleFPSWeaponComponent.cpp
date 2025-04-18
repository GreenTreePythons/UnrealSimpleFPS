// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleFPSWeaponComponent.h"
#include "SimpleFPSCharacter.h"
#include "SimpleFPSProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SimpleFPS/Widget/IngameWidget.h"
#include "SimpleFPSGameMode.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USimpleFPSWeaponComponent::USimpleFPSWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	MaxBulletCount = 30;
}

void USimpleFPSWeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (CurrentBulletCount == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("not enough bullet"));
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<ASimpleFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
			CurrentBulletCount--;
			// ASimpleFPSGameMode* GameMode = Cast<ASimpleFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			// GameMode->IngameWidget->RefreshBulletCount();
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

bool USimpleFPSWeaponComponent::AttachWeapon(ASimpleFPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<USimpleFPSWeaponComponent>())
	{
		return false;
	}

	CurrentBulletCount = 30;
	UE_LOG(LogTemp, Error, TEXT("Current Bullet Count: %d"), CurrentBulletCount);

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &USimpleFPSWeaponComponent::Fire);
		}
	}

	Character->OnWeaponAttached.Broadcast(this);

	return true;
}

void USimpleFPSWeaponComponent::DettachWeapon()
{
	if (!Character) return;

	// Detach
	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	DetachFromComponent(DetachmentRules);

	SetSimulatePhysics(false);
	
	// set detached weapon dir
	FVector ForwardOffset = Character->GetActorForwardVector() * 50.0f;  // 50 units in front
	FVector ThrowStartLocation = GetComponentLocation() + ForwardOffset;
	SetWorldLocation(ThrowStartLocation);
	
	// set physics simulate
	SetSimulatePhysics(true);
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FVector ThrowDirection = Character->GetControlRotation().Vector();
	FVector PlayerVelocity = Character->GetVelocity();  // To add momentum
	float ThrowStrength = 1200.0f;  // Adjust this for a smoother throw
	FVector FinalThrowVelocity = (ThrowDirection * ThrowStrength) + (PlayerVelocity * 0.5f);
	AddForce(FinalThrowVelocity * GetMass(), NAME_None, true);

	// remove input context
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->ClearActionBindings();
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Weapon detached successfully!"));
}

void USimpleFPSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);
			}
		}
	}

	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}
