// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.generated.h"

enum class EWeaponType : uint8
{
	Rifle,
	Pistol
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType = EWeaponType::Rifle;
	float Accuracy = 0.8f;
	float FireRate = 0.5f;
	float BaseDamage = 10.0f;
	int32 MagazineSize = 8;
	float ReloadTime = 4.0f;
};

USTRUCT(BlueprintType)
struct FBarrelStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FFinalWeaponStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.8f;
	float FireRate = 0.5f;
	float BaseDamage = 10.0f;
	int32 MagazineSize = 8;
	float ReloadTime = 4.0f;
};

UCLASS()
class AGP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	UWeaponComponent();
	void SetWeaponStats(FWeaponStats NewWeaponStats)
	{
		WeaponStats.Accuracy = NewWeaponStats.Accuracy;
		WeaponStats.FireRate = NewWeaponStats.FireRate;
		WeaponStats.BaseDamage = NewWeaponStats.BaseDamage;
		WeaponStats.MagazineSize = NewWeaponStats.MagazineSize;
		WeaponStats.ReloadTime = NewWeaponStats.ReloadTime;
	}
	
	void SetBarrelStats(FBarrelStats NewBarrelStats)
	{
		BarrelStats.Accuracy = NewBarrelStats.Accuracy;
		BarrelStats.FireRate = NewBarrelStats.FireRate;
		BarrelStats.BaseDamage = NewBarrelStats.BaseDamage;
		BarrelStats.MagazineSize = NewBarrelStats.MagazineSize;
		BarrelStats.ReloadTime = NewBarrelStats.ReloadTime;
	}
	
	void SetFinalStats()
	{
		FinalWeaponStats.Accuracy = WeaponStats.Accuracy + BarrelStats.Accuracy;
		FinalWeaponStats.FireRate = WeaponStats.FireRate - BarrelStats.FireRate;
		FinalWeaponStats.BaseDamage = WeaponStats.BaseDamage + BarrelStats.BaseDamage;
		FinalWeaponStats.MagazineSize = WeaponStats.MagazineSize + BarrelStats.MagazineSize;
		FinalWeaponStats.ReloadTime = WeaponStats.ReloadTime - BarrelStats.ReloadTime;
	}
	
	int32 Ammo;
	bool IsReloading = false;
	float CurrentReloadTime;
	float EnemyReloadTime; 
	void Reload();

	FWeaponStats WeaponStats;
	FBarrelStats BarrelStats;
	FFinalWeaponStats FinalWeaponStats;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 RoundsRemainingInMagazine;
	float TimeSinceLastShot = 0.0f;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Fire(const FVector& BulletStart, const FVector& FireAtLocation);
};
