// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPathfindingSubsystem;

UCLASS()
class AGP_API AEnemyCharacter : public ACharacter
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

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
