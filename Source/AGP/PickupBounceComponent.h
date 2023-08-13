// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PickupBounceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP_API UPickupBounceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupBounceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void TickBounce(const float& DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditInstanceOnly)
	float CurrentAlpha;
	UPROPERTY(EditInstanceOnly)
	float CurrentTime;
	float LerpAlpha;
	bool GoBack;
	FVector StartPos;
	FVector CurrentPos;
	FVector TargetPos;
	
};
