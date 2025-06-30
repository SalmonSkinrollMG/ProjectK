// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMC_LevelBasedModifier.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API UGMMC_LevelBasedModifier : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UGMMC_LevelBasedModifier();

private:

	FGameplayEffectAttributeCaptureDefinition AttributeDefinition;

	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
