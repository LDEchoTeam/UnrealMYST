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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float Range;

private:
	void StartHoverInteraction();
	void StopHoverInteraction();

	TArray<UInteractableComponent*> TraceForInteractables();

};
