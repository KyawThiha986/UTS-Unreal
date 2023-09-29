// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

#include "../Characters/PlayerCharacter.h"

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateWeaponPickup();
	UpdateWeaponPickupMaterial();
}

void AWeaponPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipWeapon(true, WeaponPickupStats);
		Destroy();
	}
}

void AWeaponPickup::GenerateWeaponPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		WeaponRarity = EWeaponRarity::Legendary;
		MaxRoll = 4;
		RollStats();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		WeaponRarity = EWeaponRarity::Master;
		MaxRoll = 3;
		RollStats();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		WeaponRarity = EWeaponRarity::Rare;
		MaxRoll = 2;
		RollStats();
	}

	else
	{
		WeaponRarity = EWeaponRarity::Common;
		WeaponPickupStats.Accuracy = FMath::RandRange(0.9f, 0.98f);
		WeaponPickupStats.FireRate = FMath::RandRange(0.2f, 1.0f);
		WeaponPickupStats.BaseDamage = FMath::RandRange(5.0f, 15.0f);
		WeaponPickupStats.MagazineSize = FMath::RandRange(1, 19);
		WeaponPickupStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
	}

	//Determine the stats depending on whether it is good or bad
}

void AWeaponPickup::RollStats()
{
	bool IsAccuracyGood = false;
	bool IsFireRateGood = false;
	bool IsDamageGood = false;
	bool IsMagSizeGood = false;
	bool IsReloadTimeGood = false;
	int32 GoodPick;
	int32 CurrentRoll = 1;

	WeaponPickupStats.Accuracy = FMath::RandRange(0.9f, 0.98f);
	WeaponPickupStats.FireRate = FMath::RandRange(0.2f, 1.0f);
	WeaponPickupStats.BaseDamage = FMath::RandRange(5.0f, 15.0f);
	WeaponPickupStats.MagazineSize = FMath::RandRange(1, 19);
	WeaponPickupStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);

	while (CurrentRoll <= MaxRoll)
	{
		while (true)
		{
			GoodPick = FMath::RandRange(1, 5);
			if (GoodPick == 1 && IsAccuracyGood == false)
			{
				IsAccuracyGood = true;
				WeaponPickupStats.Accuracy = FMath::RandRange(0.98f, 1.0f);
				CurrentRoll += 1;
				break;
			}
			if (GoodPick == 2 && IsFireRateGood == false)
			{
				IsFireRateGood = true;
				WeaponPickupStats.FireRate = FMath::RandRange(0.05f, 0.2f);
				CurrentRoll += 1;
				break;
				
			}
			if (GoodPick == 3 && IsDamageGood == false)
			{
				IsFireRateGood = true;
				WeaponPickupStats.BaseDamage = FMath::RandRange(15.0f, 30.0f);
				CurrentRoll += 1;
				break;
			}
			if (GoodPick == 4 && IsMagSizeGood == false)
			{
				IsMagSizeGood = true;
				WeaponPickupStats.MagazineSize = FMath::RandRange(20, 100);
				CurrentRoll += 1;
				break;
			}
			if (GoodPick == 5 && IsReloadTimeGood == false)
			{
				IsReloadTimeGood = true;
				WeaponPickupStats.ReloadTime = FMath::RandRange(0.1f, 1.0f);
				CurrentRoll += 1;
				break;
			}
		}		
	}
}
