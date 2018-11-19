#pragma once

#include "CoreMinimal.h"

#include "Components/PointLightComponent.h"

#include "GlowLightComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Lights, Common), ShowCategories=(LightShafts), EditInlineNew, meta=(BlueprintSpawnableComponent))
class UNREALMYST_API UGlowLightComponent : public UPointLightComponent
{
	GENERATED_BODY()

public:
	UGlowLightComponent();
};
