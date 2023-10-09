// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "DDSFile.h"
#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	bReplicates = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletStartPosition = CreateDefaultSubobject<USceneComponent>("Bullet Start");
	BulletStartPosition->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Fire(const FVector& FireAtLocation)
{
	if (HasWeapon())
	{
		return WeaponComponent->Fire(BulletStartPosition->GetComponentLocation(),FireAtLocation);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseCharacter::HasWeapon()
{
	if (WeaponComponent)
	{
		return true;
	}
	return false;
}

void ABaseCharacter::EquipWeapon(bool bEquipWeapon, const FWeaponStats NewWeaponStats)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		EquipWeaponImplementation(bEquipWeapon, NewWeaponStats);
		MulticastEquipWeapon(bEquipWeapon);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::EquipWeaponImplementation(bool bEquipWeapon, const FWeaponStats& NewWeaponStats)
{
	// If the player or enemy tries to equip a weapon and currently doesn't have one, add and register weapon component 
	if (bEquipWeapon && !HasWeapon())
	{
		WeaponComponent = NewObject<UWeaponComponent>(this);
		WeaponComponent->RegisterComponent();
		IsWeaponEquipped = true;
	}
	else if (!bEquipWeapon && HasWeapon())
		// If the player or enemy tries to unequip a weapon and currently has one equipped, unregister weapon component and remove it completely 
		{
		WeaponComponent->UnregisterComponent();
		WeaponComponent = nullptr;
		IsWeaponEquipped = false;
		}

	// At this point we should have a WeaponComponent if we are trying to equip a weapon.
	if (HasWeapon())
	{
		// Set the weapons stats to the given weapon stats.
		WeaponComponent -> SetWeaponStats(NewWeaponStats);
		WeaponComponent -> Ammo = WeaponComponent -> WeaponStats.MagazineSize;
		CheckStatCap();
		if(WeaponComponent)
		{
			OutputWeaponStatLog();
		}
	}
	EquipWeaponGraphical(bEquipWeapon);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, WeaponComponent);
}

void ABaseCharacter::MulticastEquipWeapon_Implementation(bool bEquipWeapon)
{
	EquipWeaponGraphical(bEquipWeapon);
}

