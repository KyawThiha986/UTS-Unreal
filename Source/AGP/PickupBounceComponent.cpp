// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBounceComponent.h"

// Sets default values for this component's properties
UPickupBounceComponent::UPickupBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickupBounceComponent::BeginPlay()
{
	Super::BeginPlay();

	StartPos = GetOwner()->GetActorLocation();
	TargetPos = FVector(StartPos.X, StartPos.Y, StartPos.Z + 50);
	CurrentAlpha = -0.1f;
	GoBack = false;
}

void UPickupBounceComponent::TickBounce(const float& DeltaTime)
{
	CurrentPos = GetOwner()->GetActorLocation();
	CurrentAlpha;
	CurrentPos = FMath::Lerp(StartPos, TargetPos, CurrentAlpha);
	CurrentTime += DeltaTime / 2;

	if (CurrentAlpha <= 0.0f)
	{
		GoBack = false;
	}
	else if (CurrentAlpha >= 1.0f)
	{
		GoBack = true;
	}
	
	if (GoBack == false)
	{
		CurrentAlpha += DeltaTime / 2;
	}
	else
	{
		CurrentAlpha -= DeltaTime / 2;
	}
	GetOwner()->SetActorLocation(CurrentPos);
}


// Called every frame
void UPickupBounceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TickBounce(DeltaTime);
}

