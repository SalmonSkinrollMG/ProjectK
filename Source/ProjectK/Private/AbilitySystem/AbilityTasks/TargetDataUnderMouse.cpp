// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* ThisObject = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return ThisObject;
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (PC)
	{
		FHitResult CursorHit;
		PC->GetHitResultUnderCursor(ECC_Visibility , false , CursorHit);
		DrawDebugSphere(
		GetWorld(),
		CursorHit.ImpactPoint,
		10.0f, // Radius
		12,
		CursorHit.bBlockingHit?FColor::Yellow:FColor::Blue,
		false,
		.50f
	);

		FGameplayAbilityTargetDataHandle DataHandle;
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData->HitResult = CursorHit;
		DataHandle.Add(TargetData);

		AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			MouseTargetData.Broadcast(DataHandle);
		}
	}
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle,
			ActivationPredictionKey).AddUObject(this , &ThisClass::OnTargetDataReplicatedCallback);
		if (const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey))
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag GameplayTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle() , GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		MouseTargetData.Broadcast(GameplayAbilityTargetDataHandle);
	}
}


