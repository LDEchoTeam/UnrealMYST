#include "InteractorComponent.h"


UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Range = 200.0;
}

void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StartHoverInteraction();
	StopHoverInteraction();
}


void UInteractorComponent::StartTouchInteraction()
{
	TArray<UInteractableComponent*> interactables = TraceForInteractables();

	for(UInteractableComponent* interactable : interactables)
	{
		interactable->StartTouchInteraction.Broadcast(this);
		StartedTouchInteraction.Broadcast(interactable);
	}
}

void UInteractorComponent::StopTouchInteraction()
{
	TArray<UInteractableComponent*> interactables = TraceForInteractables();

	for(UInteractableComponent* interactable : interactables)
	{
		interactable->StartTouchInteraction.Broadcast(this);
		StartedTouchInteraction.Broadcast(interactable);
	}
}


void UInteractorComponent::StartHoverInteraction()
{
	
}

void UInteractorComponent::StopHoverInteraction()
{
	
}


TArray<UInteractableComponent*> UInteractorComponent::TraceForInteractables() {
	TArray<UInteractableComponent*> interactables;

	FCollisionQueryParams parameters = FCollisionQueryParams();
	parameters.bTraceComplex = true;
	parameters.bIgnoreTouches = true;

	FHitResult hit(ForceInit);

	FVector start;
	FRotator direction;

	GetOwner()->GetActorEyesViewPoint(start, direction);

	FVector end = start + direction.Vector() * Range;
	
	GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, parameters);

	if(hit.bBlockingHit)
	{
		AActor* actor = hit.GetActor();

		for(UActorComponent* component : actor->GetComponentsByClass(UInteractableComponent::StaticClass()))
		{
			UInteractableComponent* interactable = Cast<UInteractableComponent>(component);

			interactables.Add(interactable);
		}
	}

	return interactables;
}
