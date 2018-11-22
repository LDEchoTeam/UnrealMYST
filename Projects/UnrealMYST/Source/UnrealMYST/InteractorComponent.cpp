#include "InteractorComponent.h"

#include "InteractableComponent.h"


UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bInteractable = true;

	Range = 250.0;
}

void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UInteractorComponent::StartEnterInteraction);
	GetOwner()->OnActorEndOverlap.AddDynamic(this, &UInteractorComponent::StopEnterInteraction);
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateHoverInteraction();
}


void UInteractorComponent::StartTouchInteraction()
{
	TArray<UInteractableComponent*> interactables = TraceForInteractables();

	interactables.RemoveAll(
		[this](UInteractableComponent* interactable)
		{
			return !interactable->IsTouchInteractable(this);
		}
	);

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
		if(touchInteractable.IsValid() && !touchInteractable->IsPendingKill())
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

	interactables.RemoveAll(
		[this](UInteractableComponent* interactable)
		{
			return !interactable->IsHoverInteractable(this);
		}
	);

	HoverInteractables.Empty();

	for(UInteractableComponent* interactable : interactables)
	{
		TWeakObjectPtr<UInteractableComponent> hoverInteractable = interactable;

		HoverInteractables.Emplace(hoverInteractable);
	}

	for(TWeakObjectPtr<UInteractableComponent> hoverInteractable : hoverInteractables)
	{
		if(hoverInteractable.IsValid() && !hoverInteractable->IsPendingKill())
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


void UInteractorComponent::StartEnterInteraction(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor && !OtherActor->IsPendingKill())
	{
		TArray<UInteractableComponent*> interactables = SearchForInteractables(OtherActor);

		interactables.RemoveAll(
			[this](UInteractableComponent* interactable)
			{
				return !interactable->IsEnterInteractable(this);
			}
		);

		TArray<TWeakObjectPtr<UInteractableComponent>> enterInteractables;

		for(UInteractableComponent* interactable : interactables)
		{
			TWeakObjectPtr<UInteractableComponent> enterInteractable = interactable;

			enterInteractables.Emplace(enterInteractable);
		}

		EnterInteractables.Add(OtherActor, enterInteractables);

		for(UInteractableComponent* interactable : interactables)
		{
			interactable->StartEnterInteraction.Broadcast(this);
			StartedEnterInteraction.Broadcast(interactable);
		}
	}
}

void UInteractorComponent::StopEnterInteraction(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor)
	{
		TArray<TWeakObjectPtr<UInteractableComponent>> enterInteractables;

		if(EnterInteractables.RemoveAndCopyValue(OtherActor, enterInteractables))
		{
			for(TWeakObjectPtr<UInteractableComponent> enterInteractable : enterInteractables)
			{
				if(enterInteractable.IsValid() && !enterInteractable->IsPendingKill())
				{
					enterInteractable->StopEnterInteraction.Broadcast(this);
					StoppedEnterInteraction.Broadcast(enterInteractable.Get());
				}
				else
				{
					// Just make sure you test for validity if you start destroying interactables during interaction.
					StoppedEnterInteraction.Broadcast(nullptr);
				}
			}
		}
	}
}


TArray<UInteractableComponent*> UInteractorComponent::TraceForInteractables() {
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

		return SearchForInteractables(actor);
	}
	else {
		return TArray<UInteractableComponent*>();
	}
}

TArray<UInteractableComponent*> UInteractorComponent::SearchForInteractables(AActor* Actor) {
	TArray<UInteractableComponent*> interactables;

	for(UActorComponent* component : Actor->GetComponentsByClass(UInteractableComponent::StaticClass()))
	{
		UInteractableComponent* interactable = Cast<UInteractableComponent>(component);

		interactables.Add(interactable);
	}

	return interactables;
}
