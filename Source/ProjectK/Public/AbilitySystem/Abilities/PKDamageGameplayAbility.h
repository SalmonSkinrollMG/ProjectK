// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PKGameplayAbilities.h"
#include "PKDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API UPKDamageGameplayAbility : public UPKGameplayAbilities
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> ProjectileEffect;

	UPROPERTY(EditDefaultsOnly , Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypesMap;
};
