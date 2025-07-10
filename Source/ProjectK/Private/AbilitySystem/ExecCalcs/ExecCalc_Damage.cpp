// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/PKGameplayTags.h"

struct PKDamageStatics
{
	//1
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
	PKDamageStatics()
	{
		//2
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
	//3
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

	float Damage = Spec.GetSetByCallerMagnitude(FPKGameplayTags::Get().Internal_IncomingDamage);

	if (Damage > 0)
	{
		float DefenceInTarget = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().DefenseDef , EvaluateParams , DefenceInTarget);
		Damage = Damage * (UKismetMathLibrary::SafeDivide(100 , 100 + DefenceInTarget));// Defense multiplier 
	}
	
	
	const FGameplayModifierEvaluatedData ModifierEvaluatedData(UPkAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive , Damage);
	OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	
}
