// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Actors/PKAbilityActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

APKAbilityActor::APKAbilityActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void APKAbilityActor::BeginPlay()
{
	Super::BeginPlay();
}

void APKAbilityActor::ApplyGameplayEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> InGameplayEffect)
{
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
}

void APKAbilityActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap || InstantGameplayApplyPolicy == EEffectApplyPolicy::None)
	{
		ApplyGameplayEffectToTarget(TargetActor , InstantGameplayEffect);
	}
	if (DurationGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap || DurationGameplayApplyPolicy == EEffectApplyPolicy::None)
	{
		ApplyGameplayEffectToTarget(TargetActor , DurationGameplayEffect);
	}
	if (InfiniteGameplayApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap || InfiniteGameplayApplyPolicy == EEffectApplyPolicy::None)
	{
		ApplyGameplayEffectToTarget(TargetActor , InfiniteGameplayEffect);
	}
}

void APKAbilityActor::OnEndOverlap(AActor* TargetActor)
{
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

