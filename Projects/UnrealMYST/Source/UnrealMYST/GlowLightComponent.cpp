#include "GlowLightComponent.h"

#include "Engine/Scene.h"


UGlowLightComponent::UGlowLightComponent()
{
	Intensity = 0.000001;
	IntensityUnits = ELightUnits::Candelas;

	AttenuationRadius = 100.0;
	SourceRadius = 10.0;

	bEnableLightShaftBloom = 1;
}
