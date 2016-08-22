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
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	//UE_LOG(LogTemp, Warning, TEXT("ActorThatOpens Assigned"));
}

void UOpenDoor::OpenDoor(){
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger volume
	if(PressurePlate->IsOverlappingActor(ActorThatOpens)){
		// If the ActorThatOpens is in the volume
		//UE_LOG(LogTemp, Warning, TEXT("Call OpenDoor"));
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it's time to close the door
	if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay){
		CloseDoor();
	}
}

