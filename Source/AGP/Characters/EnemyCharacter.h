// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPathfindingSubsystem;

UENUM(BlueprintType) // Allows us to use this enum in blueprints.

enum class EEnemyState : uint8 {

	Patrol, // This essentially gets set to 0
	Engage, // set to 1
	Evade  // set to 2

};

UCLASS()

class AGP_API AEnemyCharacter : public ABaseCharacter
{
	
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveAlongPath();

	UPROPERTY()
	UPathfindingSubsystem* PathfindingSubsystem;
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> CurrentPath;
	
	UPROPERTY(EditAnywhere)
	float PathfindingError = 150.0f; // 150 cm from target by default.

	UPROPERTY(EditAnywhere)
	EEnemyState CurrentState;

	void TickPatrol();
	void TickEngage();
	void TickEvade();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
