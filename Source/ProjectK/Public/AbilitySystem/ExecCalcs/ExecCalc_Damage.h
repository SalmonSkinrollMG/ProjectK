// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PKAbilityTypes.h"
#include "ExecCalc_Damage.generated.h"


UCLASS()
class PROJECTK_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_Damage();
	void CalculateCriticalHit(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                          FAggregatorEvaluateParameters EvaluateParams,
	                          FPKGameplayEffectContext* PKEffectContext) const;
	float CalculateCritDamage(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                         FAggregatorEvaluateParameters EvaluateParams, FPKGameplayEffectContext* PKEffectContext) const;
	float CalculateTargetDefenceMultiplier(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                      FAggregatorEvaluateParameters EvaluateParams) const;
	void GetFinalDamageAfterResistance(float& Damage, float& Resistance) const;

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	
};
