// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "PKAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API UPKAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
