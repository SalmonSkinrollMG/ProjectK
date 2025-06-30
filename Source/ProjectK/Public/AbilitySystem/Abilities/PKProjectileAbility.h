// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PKGameplayAbilities.h"
#include "PKProjectileAbility.generated.h"

class APKProjectile;
/**
 * 
 */
UCLASS()
class PROJECTK_API UPKProjectileAbility : public UPKGameplayAbilities
{
	GENERATED_BODY()

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<APKProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable , Category="AbilitiesTasks|Firebolt")
	void SpawnProjectileAtSocket();
};
