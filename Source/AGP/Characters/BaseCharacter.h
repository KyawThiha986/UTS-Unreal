// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Pickups/WeaponComponent.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class AGP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	bool HasWeapon();

	void EquipWeapon(bool bEquipWeapon, const FWeaponStats NewWeaponStats);
	UFUNCTION(BlueprintImplementableEvent)
	void EquipWeaponGraphical(bool bEquipWeapon);
	bool IsWeaponEquipped = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * A scene component to store the position that hit scan shots start from. For the enemy character this could
	 * be placed close to the guns position for example and for the player character it can be placed close to the
	 * camera position.
	 */
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletStartPosition;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	/**
	 * Will fire at a specific location and handles the impact of the shot such as determining what it hit and
	 * deducting health if it hit a particular type of actor.
	 * @param FireAtLocation The location that you want to fire at.
	 * @return true if a shot was taken and false otherwise.
	 */
	void Fire(const FVector& FireAtLocation);
	void CheckStatCap()
	{
		if(WeaponComponent -> FinalWeaponStats.Accuracy > 0.999f)
		{
			WeaponComponent -> FinalWeaponStats.Accuracy = 0.999f;
		}
		
		if(WeaponComponent -> FinalWeaponStats.FireRate < 0.015f)
		{
			WeaponComponent -> FinalWeaponStats.FireRate = 0.015f;
		}
		
		if(WeaponComponent -> FinalWeaponStats.ReloadTime < 0.2f)
		{
			WeaponComponent -> FinalWeaponStats.ReloadTime = 0.2f;
		}
	};

	void OutputWeaponStatLog()
	{
		AccuracyPercentage = WeaponComponent -> WeaponStats.Accuracy * 100.0f;
		UE_LOG(LogTemp, Warning, TEXT("Weapon Stats"));
		UE_LOG(LogTemp, Log, TEXT("Accuracy: %f%%"), AccuracyPercentage);
		UE_LOG(LogTemp, Log, TEXT("FireRate: %fs"), WeaponComponent -> WeaponStats.FireRate);
		UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> WeaponStats.BaseDamage);
		UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> WeaponStats.MagazineSize);
		UE_LOG(LogTemp, Log, TEXT("Reload Time: %fs"), WeaponComponent -> WeaponStats.ReloadTime);
	}
	
	UPROPERTY(Replicated)
	UWeaponComponent* WeaponComponent = nullptr;

	int32 Ammo;
	bool IsReloading = false;
	float CurrentReloadTime;
	float EnemyReloadTime; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float BulletsPerSecond;
	float AccuracyPercentage;

	void EquipWeaponImplementation(bool bEquipWeapon,
	const FWeaponStats& WeaponStats = FWeaponStats());
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEquipWeapon(bool bEquipWeapon);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
