// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/Abilities/PKProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actors/PKProjectile.h"
#include "Interface/CombatInterface.h"
#include "Misc/PKGameplayTags.h"

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
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(SpawnRotation.Quaternion());
		
		APKProjectile* Projectile = GetWorld()->SpawnActorDeferred<APKProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());

		/*
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = TargetLocation;
		EffectContextHandle.AddHitResult(HitResult);
		EffectContextHandle.AddInstigator(GetOwningActorFromActorInfo() , Projectile);
		*/
		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(ProjectileEffect , GetAbilityLevel() , SourceASC->MakeEffectContext());
		Projectile->EffectSpecHandle = SpecHandle;

		for (auto& Pair : DamageTypesMap)
		{
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle , Pair.Key , ScaledDamage);
		}

		Projectile->FinishSpawning(SpawnTransform);
	}
}
