// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/PKAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/PKGameplayAbilities.h"

void UPKAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this , &UPKAbilitySystemComponent::ClientEffectApplied);
}

void UPKAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTags;
	GameplayEffectSpec.GetAllAssetTags(GameplayTags);
	OnEffectApplied.Broadcast(GameplayTags);
}

void UPKAbilitySystemComponent::AddCharacterAbilites(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAdd)
{
	for (const auto Ability : AbilitiesToAdd)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability , 1.0);

		if (UPKGameplayAbilities* PkGameplayAbilities = Cast<UPKGameplayAbilities>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(PkGameplayAbilities->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UPKAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& Tag)
{
	if (Tag.IsValid())
	{
		for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
			{
				AbilitySpecInputPressed(AbilitySpec);
				if (!AbilitySpec.IsActive())
				{
					TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
	}
}

void UPKAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& Tag)
{
	if (Tag.IsValid())
	{
		for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
			{
				AbilitySpecInputReleased(AbilitySpec);
			}
		}
	}
}
