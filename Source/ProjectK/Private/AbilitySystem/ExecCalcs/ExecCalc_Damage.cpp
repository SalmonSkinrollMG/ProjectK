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
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage)
	PKDamageStatics()
	{
		//2
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Defense, Target , false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Attack, Source , false);
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

	RelevantAttributesToCapture.Add(GetDamageStatics().AttackDef);
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

	//This Damage is got from the projectile ability of a particular Damage type , where we take the damage based on curve.
	float Damage = Spec.GetSetByCallerMagnitude(FPKGameplayTags::Get().Attributes_Damage_DamageDelt);

	for (const TTuple DamageTypeToResistance : FPKGameplayTags::Get().Attributes_DamageTypesToResistanceMap)
	{
		//Here we can Decrease/Increase the Damage based on the Damage Type applied.
		//GetSetByCallerMagnitude has the check for Tags . The Damage Value of this particular tag will be added to the damage.
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeToResistance.Key);
		Damage += DamageTypeValue;
	}

	//Get PKEffectContext.
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FGameplayEffectContext* EffectContext = EffectContextHandle.Get();
	FPKGameplayEffectContext* PKEffectContext = static_cast<FPKGameplayEffectContext*>(EffectContext);

	if (Damage > 0)
	{
		float BaseAttack = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().AttackDef , EvaluateParams , BaseAttack);

		//Taking Damage from curve table . (The value form curve table is based on XP) -> check above.GetCallerbymagnitude.
		//This Curve table damage could be the weapom's Damage and has nothing to do with player stats.
		//For now excluding the curve table and using the player stat(Attack) for causing damage.
		//Final Damage should be Damage = WeaponAttack + Base attack (Both are based on level)
		Damage = BaseAttack * CalculateCritDamage(ExecutionParams, EvaluateParams, PKEffectContext) * CalculateTargetDefenceMultiplier(ExecutionParams, EvaluateParams);
	}
	
	const FGameplayModifierEvaluatedData ModifierEvaluatedData(UPkAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive , Damage);
	OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	
}
