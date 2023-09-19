// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "../Characters/BaseCharacter.h"
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
}

bool UWeaponComponent::Fire(const FVector& BulletStart, const FVector& FireAtLocation)
{
	// Determine if the character is able to fire.
	if (TimeSinceLastShot < WeaponStats.FireRate)
	{
		return false;
	}

	
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
	return true;
}

