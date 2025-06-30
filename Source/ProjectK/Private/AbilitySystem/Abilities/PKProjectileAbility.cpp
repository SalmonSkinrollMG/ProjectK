// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/Abilities/PKProjectileAbility.h"

#include "Actors/PKProjectile.h"
#include "Interface/CombatInterface.h"

void UPKProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);

	if (!bIsServer)
	{
		return;
	}

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketVector();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		
		APKProjectile* Projectile = GetWorld()->SpawnActorDeferred<APKProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);

	}

	
	
}
