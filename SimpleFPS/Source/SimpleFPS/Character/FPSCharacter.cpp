// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleFPS/Weapon/BaseWeaponComponent.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "SimpleFPS/GameMode/InGameMode.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EquipedWeapon = nullptr;

	DefaultSpeed = 600.0f;
	DashSpeed = 1200.0f;
	bIsDashing = false;
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	BodyMesh = GetMesh();
	BodyMesh->SetupAttachment(GetCapsuleComponent());

	BodyMesh->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));
	BodyMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
	if (MeshFinder.Succeeded())
	{
		BodyMesh->SetSkeletalMesh(MeshFinder.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPClass(TEXT("/Game/FirstPersonArms/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP_C"));
	if (AnimBPClass.Succeeded())
	{
		BodyMesh->SetAnimInstanceClass(AnimBPClass.Class);
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
			
			UInputMappingContext* InputMappingContext = LoadObject<UInputMappingContext>(
				nullptr,
				TEXT("/Game/First/Input/IMC_Default.IMC_Default")
			);

			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to load InputMappingContext!"));
			}
		}
	}

	if (AInGameMode* GameMode = Cast<AInGameMode>(GetWorld()->GetAuthGameMode()))
	{
		IngameWidget = GameMode->IngameWidget;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_Jump.IA_Jump"));
	if (JumpActionFinder.Succeeded()) JumpAction = JumpActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_Move.IA_Move"));
	if (MoveActionFinder.Succeeded()) MoveAction = MoveActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_Look.IA_Look"));
	if (LookActionFinder.Succeeded()) LookAction = LookActionFinder.Object;

	// static ConstructorHelpers::FObjectFinder<UInputAction> DashActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_Dash.IA_Dash"));
	// if (DashActionFinder.Succeeded()) DashAction = DashActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> ShootActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_Shoot.IA_Shoot"));
	if (ShootActionFinder.Succeeded()) ShootAction = ShootActionFinder.Object;

	// static  ConstructorHelpers::FObjectFinder<UInputAction> PickupWeaponActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_PickupWeapon.IA_PickupWeapon"));
	// if (PickupWeaponActionFinder.Succeeded()) PickupWeaponAction = PickupWeaponActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> DropWeaponActionFinder(TEXT("/Game/FirstPerson/Input/Actions/IA_DropWeapon.IA_DropWeapon"));
	if (DropWeaponActionFinder.Succeeded()) DropWeaponAction = DropWeaponActionFinder.Object;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopJump);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartDash);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPSCharacter::StartDash);
		EnhancedInputComponent->BindAction(PickupWeaponAction, ETriggerEvent::Triggered, this, &AFPSCharacter::PickupWeapon);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Shoot);
	}
}

void AFPSCharacter::EquipWeapon(UBaseWeaponComponent* NewWeapon)
{
	EquipedWeapon = NewWeapon;
}

void AFPSCharacter::SetNearbyWeapon(UBaseWeaponComponent* Weapon)
{
	UE_LOG(LogTemp, Error, TEXT("near weapon updated"));
	NearbyWeapon = Weapon;
	if (IngameWidget)
	{
		IngameWidget->ShowEquipWeaponUI(Weapon != nullptr);
	}
}

const FWeaponData* AFPSCharacter::GetWeaponData()
{
	return EquipedWeapon ? &EquipedWeapon->GetWeaponData() : nullptr;
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AFPSCharacter::StartJump()
{
	Jump();
}

void AFPSCharacter::StopJump()
{
	StopJumping();
}

void AFPSCharacter::StartDash()
{
	if (!bIsDashing)
	{
		bIsDashing = true;
		GetCharacterMovement()->MaxWalkSpeed = DashSpeed;

		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			StopDash();
		});
	}
}

void AFPSCharacter::StopDash()
{
	bIsDashing = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

void AFPSCharacter::PickupWeapon()
{
	if (EquipedWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already holding a weapon! Drop it first."));
		return;
	}

	if (NearbyWeapon)
	{
		NearbyWeapon->PickupWeapon(this);
		EquipedWeapon = NearbyWeapon;
		NearbyWeapon = nullptr;
	}
}

void AFPSCharacter::DropWeapon()
{
	if (!EquipedWeapon) return;
	EquipedWeapon->DropWeapon();
	EquipedWeapon = nullptr;
}

void AFPSCharacter::Shoot()
{
	if (!EquipedWeapon) return;
	EquipedWeapon->Fire();
}



