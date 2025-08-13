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

	DECLARE_ATTRIBUTE_CAPTUREDEF(ElementalResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	PKDamageStatics()
	{
		//2
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Defense, Target , false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,Attack, Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,CritRate, Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,CritDamage, Source , false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,ElementalResistance, Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPkAttributeSet ,PhysicalResistance, Target , false);

		const FPKGameplayTags& Tags = FPKGameplayTags::Get();

		TagsToCaptureDefs.Add(Tags.Attribute_Primary_Defense , DefenseDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Primary_Attack , AttackDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CritRate , CritRateDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CritDamage, CritDamageDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Primary_ElementalResistance, ElementalResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Primary_PhysicalResistance, PhysicalResistanceDef);
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

	RelevantAttributesToCapture.Add(GetDamageStatics().ElementalResistanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().PhysicalResistanceDef);
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

void UExecCalc_Damage::GetFinalDamageAfterResistance(float& Damage, float& Resistance) const
{
	Resistance = FMath::Clamp(Resistance, 0.0f, 100.0f);

	Resistance = 1.0f - Resistance / 100.0f; // Multiplier of damage reduction
	Resistance = FMath::Max(Resistance, 0.05f); // This is to make sure that the damage is not zero at any cost , even when resistance is 100%. (0.05 is 5% of base) .
	Damage *= Resistance;
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
	
	
	float Damage = 0.0f;
	for (const TTuple<FGameplayTag, FGameplayTag> DamageTypeToResistance : FPKGameplayTags::Get().DamageTypesToResistanceMap)
	{
		//Here we can Decrease/Increase the Damage based on the Damage Type applied.
		//GetSetByCallerMagnitude has the check for Tags . The Damage Value of this particular tag will be added to the damage.

		const FGameplayTag DamageTag= DamageTypeToResistance.Key;
		const FGameplayTag ResistanceTag = DamageTypeToResistance.Value;

		//Getting the Damage of this attack.
		Damage += Spec.GetSetByCallerMagnitude(DamageTag);
		
		checkf(PKDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("Can't capture an invalid Damage, Add Resistance type %s this calc"),*ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = PKDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float Resistance = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition , EvaluateParams , Resistance);		
		GetFinalDamageAfterResistance(Damage, Resistance);
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
		Damage += BaseAttack * CalculateCritDamage(ExecutionParams, EvaluateParams, PKEffectContext) * CalculateTargetDefenceMultiplier(ExecutionParams, EvaluateParams);
	}
	
	const FGameplayModifierEvaluatedData ModifierEvaluatedData(UPkAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive , Damage);
	OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	
}
