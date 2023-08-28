// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "Components/BoxComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Creates and attaches the Actor Components to this actor.
	PickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Collider"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	// Specifies that the root transform of this actor should be the transform of the
	// Collider component.
	SetRootComponent(PickupCollider);
	// Attaches the static mesh component to be a child of the collider. This means
	// that when the actor's root transform is moved (i.e. the collider transform)
	// then the mesh will move with it.
	PickupMesh->SetupAttachment(GetRootComponent());
}

void APickupBase::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap detected"))
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupCollider -> OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickupOverlap);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

