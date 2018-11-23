#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"

#include "InteractorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedTouchInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedTouchInteraction, UInteractableComponent*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedHoverInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedHoverInteraction, UInteractableComponent*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedEnterInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedEnterInteraction, UInteractableComponent*, Interactable);


UCLASS(ClassGroup=(Interaction), Blueprintable, meta=(BlueprintSpawnableComponent))
class UNREALMYST_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(Category="Interaction", BlueprintCallable)
	void StartTouchInteraction();

	UFUNCTION(Category="Interaction", BlueprintCallable)
	void StopTouchInteraction();

	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartedTouchInteraction StartedTouchInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStoppedTouchInteraction StoppedTouchInteraction;
	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartedHoverInteraction StartedHoverInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStoppedHoverInteraction StoppedHoverInteraction;
	
	UPROPERTY(Category="Interaction", BlueprintAssignable)
    FStartedEnterInteraction StartedEnterInteraction;

	UPROPERTY(Category="Interaction", BlueprintAssignable)
	FStoppedEnterInteraction StoppedEnterInteraction;

	
	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere)
	bool bInteractable;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bLimitToInteractableComponentClass;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, NoClear, meta=(EditCondition="bLimitToInteractableComponentClass", DisplayName="Limit to Interactable"))
	TSubclassOf<class UInteractableComponent> InteractableComponentClass;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bLimitToRange;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bLimitToRange", DisplayName="Limit to Range", ClampMin="1.0"))
	float Range;

	UPROPERTY(Category="Interaction", BlueprintReadWrite, EditAnywhere, meta=(ClampMin="1.0"))
	float Trace;

private:
	TArray<TWeakObjectPtr<UInteractableComponent>> TouchInteractables;
	TArray<TWeakObjectPtr<UInteractableComponent>> HoverInteractables;

	TMap<AActor*, TArray<TWeakObjectPtr<UInteractableComponent>>> EnterInteractables;


	void UpdateHoverInteraction();


	UFUNCTION()
	void StartEnterInteraction(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void StopEnterInteraction(AActor* OverlappedActor, AActor* OtherActor);
	

	TArray<UInteractableComponent*> TraceForInteractables();
	TArray<UInteractableComponent*> SearchForInteractables(AActor* Actor);

};
