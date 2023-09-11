// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "AGP/Pathfinding/PathfindingSubsystem.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PathfindingSubsystem = GetWorld()->GetSubsystem<UPathfindingSubsystem>();
	if (PathfindingSubsystem)
	{
		CurrentPath = PathfindingSubsystem->GetRandomPath(GetActorLocation());
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find the PathfindingSubsystem"))
	}
}

void AEnemyCharacter::MoveAlongPath()
{
	// Execute the path. Should be called each tick.

	// If the path is empty do nothing.
	if (CurrentPath.IsEmpty()) return;
	
	// 1. Move towards the current stage of the path.
	//		a. Calculate the direction from the current position to the target of the current stage of the path.
	FVector MovementDirection = CurrentPath[CurrentPath.Num()-1] - GetActorLocation();
	MovementDirection.Normalize();
	//		b. Apply movement in that direction.
	AddMovementInput(MovementDirection);
	// 2. Check if it is close to the current stage of the path then pop it off.
	if (FVector::Distance(GetActorLocation(), CurrentPath[CurrentPath.Num() - 1]) < PathfindingError)
	{
		CurrentPath.Pop();
	}
}

void AEnemyCharacter::TickPatrol()
{
	if (CurrentPath.IsEmpty())
	{
		MoveAlongPath();
	}
}

void AEnemyCharacter::TickEngage()
{
	if (CurrentPath.IsEmpty())
	{
		for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It)
		{
			CurrentPath = PathfindingSubsystem->GetPath(GetActorLocation(), (*It)->GetActorLocation());
			MoveAlongPath();
			Fire((*It) -> GetActorLocation());
		}
	}
}

void AEnemyCharacter::TickEvade()
{
	for (TActorIterator<APlayerCharacter> It(GetWorld()); It; ++It)
	{
		CurrentPath = PathfindingSubsystem->GetPathAway(GetActorLocation(), (*It)->GetActorLocation());
		MoveAlongPath();
	}
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	if (CurrentState == EEnemyState::Patrol) {
		TickPatrol();
    }
	else if (CurrentState == EEnemyState::Engage)
	{
		TickEngage();
	}
	else if (CurrentState == EEnemyState::Evade)
	{
		TickEvade();
	}
	*/
	
	switch (CurrentState)
	{
	case EEnemyState::Patrol:
		TickPatrol();
		break; 

	case EEnemyState::Engage:
		TickEngage();
		break;
	case EEnemyState::Evade:
		TickEvade();
		break;

	default: break; 
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

