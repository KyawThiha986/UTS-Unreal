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
	TargetPos = FVector(StartPos.X, StartPos.Y, StartPos.Z + 100);
	CurrentAlpha = 0;
}

void UPickupBounceComponent::TickBounce(const float& DeltaTime)
{
	if (CurrentAlpha <= 0)
	{
		CurrentAlpha += DeltaTime / 2;
	}
	else if (CurrentAlpha >= 1)
	{
		CurrentAlpha -= DeltaTime / 2;
	}
	
	float LerpAlpha = FMath::Clamp<float>(CurrentAlpha, 0.0f, 1.0f);
	FVector NewPosition = FMath::Lerp(StartPos, TargetPos, LerpAlpha);
	GetOwner()->SetActorLocation(NewPosition);
}


// Called every frame
void UPickupBounceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TickBounce(DeltaTime);
}

