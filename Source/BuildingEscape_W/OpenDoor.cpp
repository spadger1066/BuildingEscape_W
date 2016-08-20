// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape_W.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	//UE_LOG(LogTemp, Warning, TEXT("ActorThatOpens Assigned"));
}

void UOpenDoor::OpenDoor(){
	// Find the Actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator newRotation = FRotator(0.f, 60.f, 0.f);

	// Set the door Rotation
	Owner->SetActorRotation(newRotation);
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger volume
	if(PressurePlate->IsOverlappingActor(ActorThatOpens)){
		// If the ActorThatOpens is in the volume
		UE_LOG(LogTemp, Warning, TEXT("Call OpenDoor"));
		OpenDoor();
	}
}

