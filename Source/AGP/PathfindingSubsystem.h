// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PathfindingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API UPathfindingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

public:
	TArray<FVector*> GetRandomPath(const FVector& StartLocation);

protected:
	UPROPERTY()
	TArray<ANavigationNode*> Nodes;

private:
	void PopulateNodes();
};
