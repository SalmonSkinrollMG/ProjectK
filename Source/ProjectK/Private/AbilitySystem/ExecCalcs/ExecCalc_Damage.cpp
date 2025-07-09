// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "AbilitySystemComponent.h"

struct PKDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
	PKDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Defense, Target , false);
	}
};

static const PKDamageStatics& GetDamageStatics()
{
	static PKDamageStatics DamageStatics;
	return DamageStatics;
}
UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageStatics().DefenseDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	float Defense = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().DefenseDef ,EvaluateParams ,Defense);
	Defense = FMath::Max<float>(0.0f , Defense);
	++Defense;

	const FGameplayModifierEvaluatedData ModifierEvaluatedData(GetDamageStatics().DefenseProperty , EGameplayModOp::Additive , Defense);
	OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	
}
