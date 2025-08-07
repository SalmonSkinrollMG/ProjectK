// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/ExecCalcs/ExecCalc_Damage.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PKAbilityTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/PKGameplayTags.h"

struct PKDamageStatics
{
	//1
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage)
	PKDamageStatics()
	{
		//2
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Defense, Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,CritRate, Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,CritDamage, Source , false);
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
	RelevantAttributesToCapture.Add(GetDamageStatics().CritRateDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritDamageDef);
}

void UExecCalc_Damage::CalculateCriticalHit(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters EvaluateParams, FPKGameplayEffectContext* PKEffectContext) const
{
	float RandomRoll = FMath::FRandRange(0.0f, 100.0f);
	float CritRate = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritRateDef , EvaluateParams , CritRate);
	if (RandomRoll <= CritRate)
	{
		PKEffectContext->SetIsCriticalHit(true);
	}
}

float UExecCalc_Damage::CalculateCritDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters EvaluateParams, FPKGameplayEffectContext* PKEffectContext) const
{
	CalculateCriticalHit(ExecutionParams , EvaluateParams , PKEffectContext);
	float CritMultiplier = 1.0f;
	float CritDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritDamageDef , EvaluateParams , CritDamage);
	if (PKEffectContext->IsCriticalHit())
	{
		CritMultiplier += (CritDamage / 100.0f); 
	}
	return CritMultiplier;
}

float UExecCalc_Damage::CalculateTargetDefenceMultiplier(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters EvaluateParams) const
{
	float DefenceInTarget = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().DefenseDef , EvaluateParams , DefenceInTarget);
	return UKismetMathLibrary::SafeDivide(100 , 100 + DefenceInTarget);
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

	//Get PKEffectContext.
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	FPKGameplayEffectContext* PKEffectContext = static_cast<FPKGameplayEffectContext*>(EffectContext);

	if (Damage > 0)
	{
		Damage = Damage * CalculateCritDamage(ExecutionParams, EvaluateParams, PKEffectContext) * CalculateTargetDefenceMultiplier(ExecutionParams, EvaluateParams);
	}
	
	const FGameplayModifierEvaluatedData ModifierEvaluatedData(UPkAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive , Damage);
	OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	
}
