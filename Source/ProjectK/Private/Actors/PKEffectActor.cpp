// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Actors/PKEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

APKEffectActor::APKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void APKEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void APKEffectActor::ApplyGameplayEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> InGameplayEffect)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanAffectEnemies)
	{
		return;
	}
	UAbilitySystemComponent* ASCTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASCTarget == nullptr)
	{
		return;
	}
	FGameplayEffectContextHandle EffectContextHandle = ASCTarget->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = ASCTarget->MakeOutgoingSpec(InGameplayEffect , EffectLevel , EffectContextHandle);
	FActiveGameplayEffectHandle GameplayEffectHandle = ASCTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteGameplayRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveGameplayEffects.Add(ASCTarget , GameplayEffectHandle);
	}

	if (!bIsInfinite)
	{
		Destroy();
	}
}

void APKEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanAffectEnemies)
	{
		return;
	}
	if (InstantGameplayEffect && InstantGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , InstantGameplayEffect);
	}
	if (DurationGameplayEffect && DurationGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , DurationGameplayEffect);
	}
	if (InfiniteGameplayEffect && InfiniteGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , InfiniteGameplayEffect);
	}
}

void APKEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bCanAffectEnemies)
	{
		return;
	}
	if (InstantGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , InstantGameplayEffect);
	}
	if (DurationGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , DurationGameplayEffect);
	}
	if (InfiniteGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor , InfiniteGameplayEffect);
	}
	if (InfiniteGameplayRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* ASCTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(ASCTarget))
		{
			FActiveGameplayEffectHandle* HandlePtr = ActiveGameplayEffects.Find(ASCTarget);
			if (HandlePtr)
			{
				FActiveGameplayEffectHandle GameplayEffectHandle = *HandlePtr;
				ActiveGameplayEffects.Remove(ASCTarget);
				ASCTarget->RemoveActiveGameplayEffect(GameplayEffectHandle);
			}
		}
	}
}

