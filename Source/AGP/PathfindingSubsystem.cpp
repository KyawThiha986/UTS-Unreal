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
			UE_LOG(LogTemp, Warning, TEXT("%s at %s"), *(*It)->GetActorNameOrLabel(),*(*It)->GetActorLocation().ToString());
		}
	}
}

/*
ANavigationNode* UPathfindingSubsystem::GetRandomNode()
{
	if(Nodes.IsEmpty())
	{
		return nullptr;
	}
	else
	{
		int32 RandNodeNumber = FMath::RandRange(0,  Nodes.Num() - 1);
		ANavigationNode* PickNode = Nodes[RandNodeNumber];
		
		return PickNode;
	}
}

ANavigationNode* UPathfindingSubsystem::FindNearestNode(const FVector& TargetLocation)
{
	if(Nodes.IsEmpty())
	{
		return nullptr;
	}
	float SmallestDistance = INFINITY;
	ANavigationNode* ShortestNode = nullptr;
	
	for (int i = 0; i < Nodes.Num(); i++)
	{
		float NodeDistance = FVector::Distance(Nodes[i]->GetActorLocation(),TargetLocation);
		if (NodeDistance < SmallestDistance)
		{
			SmallestDistance = NodeDistance;
			ShortestNode = Nodes[i];
		}
	}
	return ShortestNode;
}


TArray<FVector> UPathfindingSubsystem::GetPath(ANavigationNode* StartNode, ANavigationNode* EndNode)
{
	TArray<ANavigationNode*> OpenSet;
	ANavigationNode* CurrentNode;
	
	OpenSet.Add(StartNode);
	
	for(ANavigationNode* Node: Nodes)
	{
		if (Node != nullptr)
		{
			Node->GScore = INFINITY;
		}
	}
	
	StartNode->GScore = 0;
	StartNode->HScore = FVector::Distance(StartNode->GetActorLocation(), EndNode->GetActorLocation());

	while(!OpenSet.IsEmpty())
	{
		float MinFScore = INFINITY;
	
		for (int i = 0; i < OpenSet.Num(); i++)
		{
			StartNode->FScore = StartNode->GScore + StartNode->HScore;
			if (StartNode->FScore < MinFScore)
			{
				MinFScore = StartNode->FScore;
				CurrentNode = OpenSet[i];
			}
		}
		OpenSet.Remove(CurrentNode);
		if (CurrentNode == EndNode)
		{
			
		}
	}
}
*/


