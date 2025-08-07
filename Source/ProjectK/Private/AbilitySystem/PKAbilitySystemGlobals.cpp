// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/PKAbilitySystemGlobals.h"

#include "PKAbilityTypes.h"

FGameplayEffectContext* UPKAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FPKGameplayEffectContext;
}
