#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "InteractableComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartTouchInteraction, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStopTouchInteraction, UInteractorComponent*, Interactor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartHoverInteraction, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStopHoverInteraction, UInteractorComponent*, Interactor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartEnterInteraction, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStopEnterInteraction, UInteractorComponent*, Interactor);


UCLASS(Blueprintable, ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class UNREALMYST_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	bool IsTouchInteractable(UInteractorComponent* interactor);
	virtual bool IsTouchInteractable_Implementation(UInteractorComponent* interactor);

	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	bool IsHoverInteractable(UInteractorComponent* interactor);
	virtual bool IsHoverInteractable_Implementation(UInteractorComponent* interactor);

	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	bool IsEnterInteractable(UInteractorComponent* interactor);
	virtual bool IsEnterInteractable_Implementation(UInteractorComponent* interactor);

	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartTouchInteraction StartTouchInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStopTouchInteraction StopTouchInteraction;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartHoverInteraction StartHoverInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStopHoverInteraction StopHoverInteraction;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartEnterInteraction StartEnterInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStopEnterInteraction StopEnterInteraction;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	bool bInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float Range;

};
