// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Pickup Collider"));
	BulletStartPosition->SetupAttachment(GetRootComponent());
}

bool ABaseCharacter::HasWeapon()
{
	return bHasWeaponEquipped;
}

void ABaseCharacter::EquipWeapon(bool bEquipWeapon)
{
	bHasWeaponEquipped = bEquipWeapon;
	EquipWeaponGraphical(bEquipWeapon);
	if (bEquipWeapon)
	{
		UE_LOG(LogTemp, Display, TEXT("Player has equipped weapon."))
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Player has unequipped weapon."))
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABaseCharacter::Fire(const FVector& FireAtLocation)
{
	if(TimeSinceLastShot < MinTimeBetweenShots)
	{
		return false;
	}
	
	FHitResult OutHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation() + FVector(0,0,50), FireAtLocation, ECC_WorldStatic, Params))
	{
		
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OutHit.GetActor()))
		{
			DrawDebugLine(
				GetWorld(),
				GetActorLocation() + FVector(0,0,50),
				OutHit.ImpactPoint,
				FColor::Green,
				false,
				1, 0,
				10.0f);
		}
		
		else if (Character == nullptr)
		{
			DrawDebugLine(
				GetWorld(),
				GetActorLocation() + FVector(0,0,50),
				OutHit.ImpactPoint,
				FColor::Orange,
				false,
				1, 0,
				10.0f);
		}
	}
	else
	{
		DrawDebugLine(
			GetWorld(),
			GetActorLocation() + FVector(0,0,50),
			FireAtLocation,
			FColor::Red,
			false,
			1, 0,
			10.0f);
	}

	TimeSinceLastShot = 0.0f;
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.0f, 4, FColor::Cyan, false, -1, 0, 5.0f);
	UE_LOG(LogTemp, Warning, TEXT("Weapon Fired"))
	return true;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bHasWeaponEquipped == true)
	{
		TimeSinceLastShot += DeltaTime;
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

