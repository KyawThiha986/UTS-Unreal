// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AWeaponPickup : public APickupBase
{
	GENERATED_BODY()

public:
	
	AWeaponPickup();
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(Replicated, BlueprintReadWrite)
	EWeaponRarity WeaponRarity = EWeaponRarity::Common;

	UPROPERTY(Replicated)
	FWeaponStats WeaponPickupStats;
	void GenerateWeaponPickup();
	void RollStats();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWeaponPickupMaterial();
	int32 MaxRoll;

	//Server
	void GenerateWeaponPickupImplementation();
	UFUNCTION(Server, Reliable)
	void ServerGenerateWeaponPickup();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
