// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "BaseWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "SimpleFPS/Character/FPSCharacter.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<UBaseWeaponComponent>(TEXT("WeaponComponent"));
	RootComponent = WeaponComponent;

	PickupTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("PickupTrigger"));
	PickupTrigger->SetupAttachment(WeaponComponent);
	PickupTrigger->InitSphereRadius(100.f);

	PickupTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	PickupTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupTrigger->SetGenerateOverlapEvents(true);

	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActor::OnTriggerBeginOverlap);
	PickupTrigger->OnComponentEndOverlap.AddDynamic(this, &AWeaponActor::OnTriggerEndOverlap);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	if (PickupTrigger)
	{
		PickupTrigger->SetSphereRadius(WeaponComponent->GetWeaponData().CollisionRadius);
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
												UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
												bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnTriggerBeginOverlap : %s"), *OtherActor->GetName());
	AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
	if (Player)
	{
		Player->SetNearbyWeapon(WeaponComponent);
	}
}

void AWeaponActor::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
											  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnTriggerEndOverlap : %s"), *OtherActor->GetName());
	AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor);
	if (Player && Player->GetNearbyWeapon() == WeaponComponent)
	{
		Player->SetNearbyWeapon(nullptr);
	}
}