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
	FVector GetInteractionPosition();


	UFUNCTION(Category="Interaction", BlueprintNativeEvent)
	bool IsTouchInteractable(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintNativeEvent)
	bool IsHoverInteractable(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintNativeEvent)
	bool IsEnterInteractable(UInteractorComponent* Interactor);

	
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

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, NoClear, meta=(EditCondition="bLimitToInteractorComponentClass", DisplayName="Limit to Interactor Component Class"))
	TSubclassOf<class UInteractorComponent> InteractorComponentClass;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bLimitToRange;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bLimitToRange", DisplayName="Limit to Range", ClampMin="1.0"))
	float Range;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere)
	bool bLimitToWindow;
	
	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditInstanceOnly, meta=(EditCondition="bLimitToWindow"))
	TWeakObjectPtr<AActor> Window;

protected:
	virtual FVector GetInteractionPosition_Implementation();

	virtual bool IsTouchInteractable_Implementation(UInteractorComponent* Interactor);
	virtual bool IsHoverInteractable_Implementation(UInteractorComponent* Interactor);
	virtual bool IsEnterInteractable_Implementation(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintCallable)
	bool CheckInteractable(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintCallable)
	bool CheckClass(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintCallable)
	bool CheckRange(UInteractorComponent* Interactor);

	UFUNCTION(Category="Interaction", BlueprintCallable)
	bool CheckWindow(UInteractorComponent* Interactor);

};
