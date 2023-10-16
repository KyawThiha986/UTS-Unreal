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

void UPickupManagerSystem::SpawnPickups()
{
	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		MulticastSpawnPickup();
	}
	else if (GetWorld()->GetNetMode() == NM_ListenServer)
	{
		MulticastSpawnPickup_Implementation();
	}
	else if (GetWorld()->GetNetMode() == NM_Standalone)
	{
		SpawnPickupsImplementation();
	}
}

void UPickupManagerSystem::SpawnPickupsImplementation()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn pickups."))
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
    	AWeaponPickup* WeaponPickup = GetWorld()->SpawnActor<AWeaponPickup>(
    	GameInstance->GetWeaponPickupClass(),SpawnPosition,FRotator::ZeroRotator);
    	SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
    	1)];
    	SpawnPosition.Z += 50.0f;
    }
}

void UPickupManagerSystem::MulticastSpawnPickup_Implementation()
{
	SpawnPickupsImplementation();
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
		SpawnPickups();
		TimeSinceLastSpawn = 0.0f;
	}
}
