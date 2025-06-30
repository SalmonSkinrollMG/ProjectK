// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature , const FGameplayAbilityTargetDataHandle& , DataHandle);

UCLASS()
class PROJECTK_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& GameplayAbilityTargetDataHandle, FGameplayTag GameplayTag);
	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable , Category="GameplayAbility|Tasks" , meta=(DisplayName = "TargetDataUnderMouse" , HidePin = "OwningAbility" , DefaultToSelf = "OwningAbility") , BlueprintInternalUseOnly)
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature MouseTargetData;

	void SendMouseCursorData();
};
