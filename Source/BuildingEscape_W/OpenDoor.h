// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_W_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable, Category="Event Dispatcher")
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FDoorEvent OnClose;

private:

	UPROPERTY(EditAnywhere)
		float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 30.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;

	AActor* Owner = nullptr; // The owning door
	
	// Returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
