// It's mine! Leave it alone

#include "BuildingEscape_W.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();


	// Ray-cast out to reach distance

	// See what we hit
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Get the player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("Location %s, Rotation %s"), 
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString());

}

