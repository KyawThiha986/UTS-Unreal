// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
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

bool ABaseCharacter::Fire(const FVector& FireAtLocation)
{
	if (HasWeapon())
	{
		return WeaponComponent->Fire(BulletStartPosition->GetComponentLocation(),FireAtLocation);
	}
	return false;
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
	if (bEquipWeapon && !HasWeapon())
	{
		WeaponComponent = NewObject<UWeaponComponent>(this);
		WeaponComponent->RegisterComponent();
	}
	else if (!bEquipWeapon && HasWeapon())
	{
		WeaponComponent->UnregisterComponent();
		WeaponComponent = nullptr;
	}

	// At this point we should have a WeaponComponent if we are trying to equip a weapon.
	if (HasWeapon())
	{
		// Set the weapons stats to the given weapon stats.
		WeaponComponent->SetWeaponStats(NewWeaponStats);
		WeaponComponent -> SetFinalStats();
		WeaponComponent -> Ammo = WeaponComponent -> FinalWeaponStats.MagazineSize;
		CheckStatCap();
		if(WeaponComponent)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: %f"), WeaponComponent -> FinalWeaponStats.Accuracy);
			UE_LOG(LogTemp, Log, TEXT("FireRate: %f"), WeaponComponent -> FinalWeaponStats.FireRate);
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> FinalWeaponStats.BaseDamage);
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> FinalWeaponStats.MagazineSize);
			UE_LOG(LogTemp, Log, TEXT("Reload Time: %f"), WeaponComponent -> FinalWeaponStats.ReloadTime);
		}
	}
	
	EquipWeaponGraphical(bEquipWeapon);
}

void ABaseCharacter::EquipBarrel(const FBarrelStats NewBarrelStats)
{
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetBarrelStats(NewBarrelStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		UE_LOG(LogTemp, Log, TEXT("Accuracy: %f"), WeaponComponent -> FinalWeaponStats.Accuracy);
		UE_LOG(LogTemp, Log, TEXT("FireRate: %f"), WeaponComponent -> FinalWeaponStats.FireRate);
		UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> FinalWeaponStats.BaseDamage);
		UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> FinalWeaponStats.MagazineSize);
		UE_LOG(LogTemp, Log, TEXT("Reload Time: %f"), WeaponComponent -> FinalWeaponStats.ReloadTime);
	}
}

void ABaseCharacter::EquipSights(const FSightsStats NewSightsStats)
{
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetSightsStats(NewSightsStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		UE_LOG(LogTemp, Log, TEXT("Accuracy: %f"), WeaponComponent -> FinalWeaponStats.Accuracy);
		UE_LOG(LogTemp, Log, TEXT("FireRate: %f"), WeaponComponent -> FinalWeaponStats.FireRate);
		UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> FinalWeaponStats.BaseDamage);
		UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> FinalWeaponStats.MagazineSize);
		UE_LOG(LogTemp, Log, TEXT("Reload Time: %f"), WeaponComponent -> FinalWeaponStats.ReloadTime);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

