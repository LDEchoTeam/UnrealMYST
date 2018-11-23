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


UCLASS(ClassGroup=(Interaction), Blueprintable, meta=(BlueprintSpawnableComponent))
class UNREALMYST_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UFUNCTION(Category="Interaction", BlueprintNativeEvent)
	bool IsTouchInteractable(UInteractorComponent* Interactor);
	virtual bool IsTouchInteractable_Implementation(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintNativeEvent, Category="Interaction")
	bool IsHoverInteractable(UInteractorComponent* Interactor);
	virtual bool IsHoverInteractable_Implementation(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintNativeEvent, Category="Interaction")
	bool IsEnterInteractable(UInteractorComponent* Interactor);
	virtual bool IsEnterInteractable_Implementation(UInteractorComponent* Interactor);

	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartTouchInteraction StartTouchInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStopTouchInteraction StopTouchInteraction;
	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartHoverInteraction StartHoverInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStopHoverInteraction StopHoverInteraction;
	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartEnterInteraction StartEnterInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStopEnterInteraction StopEnterInteraction;

	
	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere)
	bool bInteractable;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bLimitToInteractorComponentClass;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, NoClear, meta=(EditCondition="bLimitToInteractorComponentClass", DisplayName="Limit to Interactor"))
	TSubclassOf<class UInteractorComponent> InteractorComponentClass;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bLimitToRange;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bLimitToRange", DisplayName="Limit to Range", ClampMin="1.0"))
	float Range;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere)
	bool bLimitToWindow;
	
	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditInstanceOnly, meta=(EditCondition="bLimitToWindow"))
	TWeakObjectPtr<AActor> Window;

private:
	bool CheckInteractable(UInteractorComponent* Interactor);
	bool CheckClass(UInteractorComponent* Interactor);
	bool CheckRange(UInteractorComponent* Interactor);
	bool CheckWindow(UInteractorComponent* Interactor);

};
