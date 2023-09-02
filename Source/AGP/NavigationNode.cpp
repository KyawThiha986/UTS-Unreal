// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationNode.h"

// Sets default values
ANavigationNode::ANavigationNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component"));
	SetRootComponent(LocationComponent);
}

// Called when the game starts or when spawned
void ANavigationNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavigationNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DrawDebugSphere(
	GetWorld(),
	FVector(GetActorLocation()),
	60.0f,
	8,
	FColor::Blue,
	false,
	-1,
	0,
	4.0f
	);

	
	for(const ANavigationNode* ConnectedNode: ConnectedNodes)
	{
		if (ConnectedNode != nullptr)
		{
			DrawDebugLine(
			GetWorld(),
			FVector(GetActorLocation()),
			FVector(ConnectedNode -> GetActorLocation()),
			FColor::Blue,
			false,
			-1,
			0,
			4.0f
			);
		}
		
	}
}

bool ANavigationNode::ShouldTickIfViewportsOnly() const
{
	return true;
}

