#include "InteractableComponent.h"

#include "InteractorComponent.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bInteractable = true;

	Range = 150.0;
}


bool UInteractableComponent::IsTouchInteractable_Implementation(UInteractorComponent* interactor)
{
	return bInteractable && interactor->bInteractable;
}

bool UInteractableComponent::IsHoverInteractable_Implementation(UInteractorComponent* interactor)
{
	return bInteractable && interactor->bInteractable;
}

bool UInteractableComponent::IsEnterInteractable_Implementation(UInteractorComponent* interactor)
{
	return bInteractable && interactor->bInteractable;
}
