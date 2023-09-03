// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfindingSubsystem.h"
#include "EngineUtils.h"
#include "NavigationNode.h"
#include "Containers/Array.h"

void UPathfindingSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	PopulateNodes();
}

TArray<FVector> UPathfindingSubsystem::GetRandomPath(const FVector& StartLocation)
{
	TArray<FVector> Paths;
	return Paths;
}

void UPathfindingSubsystem::PopulateNodes()
{
	Nodes.Empty();
	for (TActorIterator<ANavigationNode> It(GetWorld()); It; ++It)
	{
		ANavigationNode* Act = *It;
		if(Act)
		{
			Nodes.Push(Act);
			UE_LOG(LogTemp, Warning, TEXT("%s"),*(*It)->GetActorNameOrLabel());
			UE_LOG(LogTemp, Warning, TEXT("%s"),*(*It)->GetActorLocation().ToString());
		}
	}
}
