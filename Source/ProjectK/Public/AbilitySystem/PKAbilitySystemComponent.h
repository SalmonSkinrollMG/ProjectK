// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PKAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectApplied, FGameplayTagContainer& /*GameplayTag Container*/);
/**
 * 
 */
UCLASS()
class PROJECTK_API UPKAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	FOnEffectApplied OnEffectApplied;

	void AbilityActorInfoSet();

	UFUNCTION(Client , Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& GameplayEffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

	void AddCharacterAbilites(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAdd);

	void AbilityInputTagHeld(const FGameplayTag& Tag);
	void AbilityInputTagReleased(const FGameplayTag& Tag);
};
