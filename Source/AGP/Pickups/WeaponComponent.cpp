// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponPickup.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/EnemyCharacter.h"
#include "AGP/Characters/HealthComponent.h"

// Sets default values
UWeaponComponent::UWeaponComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastShot += DeltaTime;
	UE_LOG(LogTemp, Log, TEXT("Your float value: %i"), Ammo);
	if (IsReloading == true)
	{
		CurrentReloadTime += DeltaTime;
	}
	
	if (CurrentReloadTime > WeaponStats.ReloadTime && IsReloading == true)
	{
		Ammo = WeaponStats.MagazineSize;
		IsReloading = false;
		UE_LOG(LogTemp, Warning, TEXT("Weapon Reloaded!"));
	}
}

bool UWeaponComponent::Fire(const FVector& BulletStart, const FVector& FireAtLocation)
{
	// Determine if the character is able to fire.
	if (TimeSinceLastShot < WeaponStats.FireRate)
	{
		return false;
	}

	if (Ammo > 0)
	{
		FHitResult HitResult;
    	FCollisionQueryParams QueryParams;
    	QueryParams.AddIgnoredActor(GetOwner());
    	if (GetWorld()->LineTraceSingleByChannel(HitResult, BulletStart, FireAtLocation, ECC_Pawn, QueryParams))
    	{
    		if (ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitResult.GetActor()))
    		{
    			if (UHealthComponent* HitCharacterHealth = HitCharacter->GetComponentByClass<UHealthComponent>())
    			{
    				HitCharacterHealth->ApplyDamage(WeaponStats.BaseDamage);
    			}
    			DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Green, false, 1.0f);
    		}
    		else
    		{
    			DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Orange, false, 1.0f);
    		}
    		
    	}
    	else
    	{
    		DrawDebugLine(GetWorld(), BulletStart, FireAtLocation, FColor::Red, false, 1.0f);
    	}
		TimeSinceLastShot = 0.0f;
		Ammo -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

void UWeaponComponent::Reload()
{
	CurrentReloadTime = 0.0f;
	Ammo = 0;
	IsReloading = true;
	UE_LOG(LogTemp, Log, TEXT("Accuracy: %f"), WeaponStats.Accuracy);
	UE_LOG(LogTemp, Log, TEXT("FireRate: %f"), WeaponStats.FireRate);
	UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponStats.BaseDamage);
	UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponStats.MagazineSize);
	UE_LOG(LogTemp, Log, TEXT("Reload Time: %f"), WeaponStats.ReloadTime);
	//Ammo = WeaponStats.MagazineSize;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Reloaded!"));
}

