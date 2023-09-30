// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pickups/BarrelPickup.h"
#include "Pickups/WeaponPickup.h"
#include "Pickups/SightsPickup.h"
#include "Pickups/MagazinePickup.h"
#include "AGPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API UAGPGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
	UClass* GetWeaponPickupClass() const;
	UClass* GetBarrelPickupClass() const;
	UClass* GetSightsPickupClass() const;
	UClass* GetMagazinePickupClass() const;
	
	protected:
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AWeaponPickup> WeaponPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<ABarrelPickup> BarrelPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<ASightsPickup> SightsPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AMagazinePickup> MagazinePickupClass;
};
