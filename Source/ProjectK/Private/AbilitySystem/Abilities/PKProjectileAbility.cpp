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
}

void UPKProjectileAbility::SpawnProjectileTowardsTarget(const FVector& TargetLocation)
{
	bool bHasAuthority = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bHasAuthority)
	{
		return;
	}
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketVector();
		FRotator SpawnRotation = (TargetLocation - SocketLocation).Rotation();
		SpawnRotation.Pitch = 0.0f; // parallel to the Ground;
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(SpawnRotation.Quaternion());
		
		APKProjectile* Projectile = GetWorld()->SpawnActorDeferred<APKProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
