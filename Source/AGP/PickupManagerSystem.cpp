// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupManagerSystem.h"

#include "AGPGameInstance.h"
#include "Pathfinding/PathfindingSubsystem.h"

//Retrieve waypoint positions and set them as possible pickup spawns
void UPickupManagerSystem::PopulateSpawnLocations()
{
	PossibleSpawnLocations.Empty();

	UPathfindingSubsystem* WaypointPos;
	WaypointPos = GetWorld()->GetSubsystem<UPathfindingSubsystem>();
	PossibleSpawnLocations = WaypointPos -> GetWaypointPositions();
}

void UPickupManagerSystem::SpawnWeaponPickup()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon pickup."))
		return;
	}
	//Otherwise, Spawn a pickup at a position designated by random range
	if (const UAGPGameInstance* GameInstance =
	GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		FVector SpawnPosition =
		PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;
		
		AWeaponPickup* Pickup = GetWorld()->SpawnActor<AWeaponPickup>(
		GameInstance->GetWeaponPickupClass(),SpawnPosition,FRotator::ZeroRotator);
	}
}

void UPickupManagerSystem::SpawnBarrelPickup()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon pickup."))
		return;
	}
	//Otherwise, Spawn a pickup at a position designated by random range
	if (const UAGPGameInstance* GameInstance =
	GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		FVector SpawnPosition =
		PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;
		
		ABarrelPickup* Pickup = GetWorld()->SpawnActor<ABarrelPickup>(
		GameInstance->GetBarrelPickupClass(),SpawnPosition,FRotator::ZeroRotator);
	}
}

void UPickupManagerSystem::SpawnSightsPickup()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon pickup."))
		return;
	}
	//Otherwise, Spawn a pickup at a position designated by random range
	if (const UAGPGameInstance* GameInstance =
	GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		FVector SpawnPosition =
		PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;
		
		ASightsPickup* Pickup = GetWorld()->SpawnActor<ASightsPickup>(
		GameInstance->GetSightsPickupClass(),SpawnPosition,FRotator::ZeroRotator);
	}
}

void UPickupManagerSystem::SpawnMagazinePickup()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon pickup."))
		return;
	}
	//Otherwise, Spawn a pickup at a position designated by random range
	if (const UAGPGameInstance* GameInstance =
	GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		FVector SpawnPosition =
		PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;
		
		AMagazinePickup* Pickup = GetWorld()->SpawnActor<AMagazinePickup>(
		GameInstance->GetMagazinePickupClass(),SpawnPosition,FRotator::ZeroRotator);
		UE_LOG(LogTemp, Display, TEXT("Magazine Pickup Spawned"))
	}
}

void UPickupManagerSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;
	if(PossibleSpawnLocations.IsEmpty())
	{
		PopulateSpawnLocations();
	}
	if (TimeSinceLastSpawn > PickupSpawnRate)
	{
		SpawnWeaponPickup();
		SpawnBarrelPickup();
		SpawnSightsPickup();
		SpawnMagazinePickup();
		TimeSinceLastSpawn = 0.0f;
	}
}
