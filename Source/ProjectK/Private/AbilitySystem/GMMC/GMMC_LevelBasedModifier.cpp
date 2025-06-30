// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/GMMC/GMMC_LevelBasedModifier.h"

#include "AbilitySystem/PkAttributeSet.h"

UGMMC_LevelBasedModifier::UGMMC_LevelBasedModifier()
{
	AttributeDefinition.AttributeToCapture = UPkAttributeSet::GetLevelAttribute();
	AttributeDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AttributeDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(AttributeDefinition);
}

float UGMMC_LevelBasedModifier::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Level = 0.0f;
	GetCapturedAttributeMagnitude(AttributeDefinition , Spec , EvaluateParameters, Level);

	return Level;
}
