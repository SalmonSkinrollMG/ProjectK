// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PKGameplayAbilities.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API UPKGameplayAbilities : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat ScalableFloat;
};
