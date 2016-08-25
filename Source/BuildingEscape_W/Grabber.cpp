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
}

/// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle"), *GetOwner()->GetName());
	}
}

/// Look for attached Input Component - only appears at runtime
void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent){
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName());
	}
}

/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

/// Grabs an object in range
void UGrabber::Grab() {
	/// Try and reach any actors with body collision channel set
	// LINE TRACE and see if we reach any actors with physics body collision channel set 
	auto HitResult =  GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true	// allow rotation
		);
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetReachLineStart() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd(){
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If the physics component is attached
	if (PhysicsHandle->GrabbedComponent){		
		// move the objedt that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

/// Return hit for first physics body in reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
	FVector PlayerViewPointLocation;
	/// Set up query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParameters
	);
	return HitResult;
}

