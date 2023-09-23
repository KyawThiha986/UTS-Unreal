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
	UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		if (!Player->HasWeapon())
		{
			Player->EquipWeapon(true);
			Destroy();
		}
	}
}

void AWeaponPickup::GenerateWeaponPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		WeaponRarity = EWeaponRarity::Legendary;
		WeaponStats.Accuracy = FMath::RandRange(0.98f, 1.0f);
		WeaponStats.FireRate = FMath::RandRange(0.05f, 0.2f);
		WeaponStats.BaseDamage = FMath::RandRange(15.0f, 30.0f);
		WeaponStats.MagazineSize = FMath::RandRange(20, 100);
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
		WeaponStats.Accuracy = FMath::RandRange(0.9f, 0.98f);
		WeaponStats.FireRate = FMath::RandRange(0.2f, 1.0f);
		WeaponStats.BaseDamage = FMath::RandRange(5.0f, 15.0f);
		WeaponStats.MagazineSize = FMath::RandRange(1, 19);
	}

	//Determine the stats depending on whether it is good or bad
}

void AWeaponPickup::RollStats()
{
	bool IsAccuracyGood = false;
	bool IsFireRateGood = false;
	bool IsDamageGood = false;
	bool IsMagSizeGood = false;
	int32 GoodPick;
	int32 CurrentRoll = 1;

	WeaponStats.Accuracy = FMath::RandRange(0.9f, 0.98f);
	WeaponStats.FireRate = FMath::RandRange(0.2f, 1.0f);
	WeaponStats.BaseDamage = FMath::RandRange(5.0f, 15.0f);
	WeaponStats.MagazineSize = FMath::RandRange(1, 19);

	if (CurrentRoll <= MaxRoll)
	{
		while (true)
		{
			GoodPick = FMath::RandRange(1, 4);
			if (GoodPick == 1 && IsAccuracyGood == false)
			{
				IsAccuracyGood = true;
				WeaponStats.Accuracy = FMath::RandRange(0.98f, 1.0f);
				CurrentRoll += 1;
				break;
			}
			if (GoodPick == 2 && IsFireRateGood == false)
			{
				IsFireRateGood = true;
				WeaponStats.FireRate = FMath::RandRange(0.05f, 0.2f);
				CurrentRoll += 1;
				break;
				
			}
			if (GoodPick == 3 && IsDamageGood == false)
			{
				IsFireRateGood = true;
				WeaponStats.BaseDamage = FMath::RandRange(15.0f, 30.0f);
				CurrentRoll += 1;
				break;
			}
			if (GoodPick == 4 && IsMagSizeGood == false)
			{
				IsMagSizeGood = true;
				WeaponStats.MagazineSize = FMath::RandRange(20, 100);
				CurrentRoll += 1;
				break;
			}
		}		
	}
}
