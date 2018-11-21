#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"

#include "InteractableComponent.h"

#include "InteractorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedTouchInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedTouchInteraction, UInteractableComponent*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedHoverInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedHoverInteraction, UInteractableComponent*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartedEnterInteraction, UInteractableComponent*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStoppedEnterInteraction, UInteractableComponent*, Interactable);


UCLASS(Blueprintable, ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class UNREALMYST_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category="Interaction")
	void StartTouchInteraction();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void StopTouchInteraction();

	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartedTouchInteraction StartedTouchInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStoppedTouchInteraction StoppedTouchInteraction;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartedHoverInteraction StartedHoverInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStoppedHoverInteraction StoppedHoverInteraction;
	
	UPROPERTY(BlueprintAssignable, Category="Interaction")
    FStartedEnterInteraction StartedEnterInteraction;

	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FStoppedEnterInteraction StoppedEnterInteraction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float Range;

private:
	TArray<TWeakObjectPtr<UInteractableComponent>> TouchInteractables;
	TArray<TWeakObjectPtr<UInteractableComponent>> HoverInteractables;

	void UpdateHoverInteraction();

	UFUNCTION()	void StartEnterInteraction(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()	void StopEnterInteraction(AActor* OverlappedActor, AActor* OtherActor);
	
	TArray<UInteractableComponent*> TraceForInteractables();
	TArray<UInteractableComponent*> SearchForInteractables(AActor* Actor);

};
