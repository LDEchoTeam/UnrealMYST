#include "InteractableComponent.h"

#include "InteractorComponent.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bInteractable = true;

	bLimitToInteractorComponentClass = false;
	InteractorComponentClass = UInteractorComponent::StaticClass();

	bLimitToRange = false;
	Range = 150.0;

	bLimitToWindow = false;
	Window = GetOwner();
}


FVector UInteractableComponent::GetInteractionPosition_Implementation()
{
	return GetOwner()->GetActorLocation();
}


bool UInteractableComponent::IsTouchInteractable_Implementation(UInteractorComponent* Interactor)
{
	return CheckInteractable(Interactor) && CheckClass(Interactor) && CheckRange(Interactor) && CheckWindow(Interactor);
}

bool UInteractableComponent::IsHoverInteractable_Implementation(UInteractorComponent* Interactor)
{
	return CheckInteractable(Interactor) && CheckClass(Interactor) && CheckRange(Interactor) && CheckWindow(Interactor);
}

bool UInteractableComponent::IsEnterInteractable_Implementation(UInteractorComponent* Interactor)
{
	return CheckInteractable(Interactor) && CheckClass(Interactor);
}


bool UInteractableComponent::CheckInteractable(UInteractorComponent* Interactor)
{
	return bInteractable && Interactor->bInteractable;
}

bool UInteractableComponent::CheckClass(UInteractorComponent* Interactor)
{
	bool interactorComponentClassValid = !bLimitToInteractorComponentClass || Interactor->GetClass()->IsChildOf(InteractorComponentClass);
	bool interactableComponentClassValid = !Interactor->bLimitToInteractableComponentClass || GetClass()->IsChildOf(Interactor->InteractableComponentClass);

	return interactorComponentClassValid && interactableComponentClassValid;
}

bool UInteractableComponent::CheckRange(UInteractorComponent* Interactor)
{
	float range = FLT_MAX;

	if(Interactor->bLimitToRange)
	{
		range = FMath::Min(range, Interactor->Range);
	}

	if(bLimitToRange)
	{
		range = FMath::Min(range, Range);
	}

	FVector start = Interactor->GetInteractionPosition();
	FVector end = GetInteractionPosition();

	float distance = (start - end).Size();

	return distance < range;
}

bool UInteractableComponent::CheckWindow(UInteractorComponent* Interactor)
{
	return !bLimitToWindow || Window.IsValid() && Window->IsOverlappingActor(Interactor->GetOwner());
}
