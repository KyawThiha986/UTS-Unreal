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
	float Accuracy = 1.0f;
	float FireRate = 0.2f;
	float BaseDamage = 10.0f;
	int32 MagazineSize = 5;
};

UCLASS()
class AGP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UWeaponComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FWeaponStats WeaponStats;
	int32 RoundsRemainingInMagazine;
	float TimeSinceLastShot = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Fire(const FVector& BulletStart, const FVector& FireAtLocation);
};
