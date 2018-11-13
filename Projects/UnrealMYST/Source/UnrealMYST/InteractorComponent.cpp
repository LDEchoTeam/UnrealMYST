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

	UpdateHoverInteraction();
}


void UInteractorComponent::StartTouchInteraction()
{
	TArray<UInteractableComponent*> interactables = TraceForInteractables();

	for(UInteractableComponent* interactable : interactables)
	{
		TWeakObjectPtr<UInteractableComponent> touchInteractable = interactable;

		TouchInteractables.Emplace(touchInteractable);
	}

	for(UInteractableComponent* interactable : interactables)
	{
		interactable->StartTouchInteraction.Broadcast(this);
		StartedTouchInteraction.Broadcast(interactable);
	}
}

void UInteractorComponent::StopTouchInteraction()
{
	for(TWeakObjectPtr<UInteractableComponent> touchInteractable : TouchInteractables)
	{
		if(touchInteractable.IsValid() && !touchInteractable->IsPendingKill() && touchInteractable->GetOwner())
		{
			touchInteractable->StopTouchInteraction.Broadcast(this);
			StoppedTouchInteraction.Broadcast(touchInteractable.Get());
		}
		else
		{
			// Just make sure you test for validity if you start destroying interactables during interaction.
			StoppedHoverInteraction.Broadcast(nullptr);
		}
	}

	TouchInteractables.Empty();
}


void UInteractorComponent::UpdateHoverInteraction()
{
	// Copy the list so we can update the public state of the list first.
	TArray<TWeakObjectPtr<UInteractableComponent>> hoverInteractables = HoverInteractables;

	TArray<UInteractableComponent*> interactables = TraceForInteractables();

	HoverInteractables.Empty();

	for(UInteractableComponent* interactable : interactables)
	{
		TWeakObjectPtr<UInteractableComponent> hoverInteractable = interactable;

		HoverInteractables.Emplace(hoverInteractable);
	}

	for(TWeakObjectPtr<UInteractableComponent> hoverInteractable : hoverInteractables)
	{
		if(hoverInteractable.IsValid() && !hoverInteractable->IsPendingKill() && hoverInteractable->GetOwner())
		{
			if(!interactables.Contains(hoverInteractable.Get()))
			{
				hoverInteractable->StopHoverInteraction.Broadcast(this);
				StoppedHoverInteraction.Broadcast(hoverInteractable.Get());
			}
		}
		else
		{
			// Just make sure you test for validity if you start destroying interactables during interaction.
			StoppedHoverInteraction.Broadcast(nullptr);
		}
	}

	for(UInteractableComponent* interactable : interactables)
	{
		if(!hoverInteractables.Contains(TWeakObjectPtr<UInteractableComponent>(interactable)))
		{
			interactable->StartHoverInteraction.Broadcast(this);
			StartedHoverInteraction.Broadcast(interactable);
		}
	}
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
