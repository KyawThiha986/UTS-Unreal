// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingSubsystem.h"

void UPathfindingSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

TArray<FVector*> UPathfindingSubsystem::GetRandomPath(const FVector& StartLocation)
{
	TArray<FVector*> Paths;
	return Paths;
}

void UPathfindingSubsystem::PopulateNodes()
{
	
}
