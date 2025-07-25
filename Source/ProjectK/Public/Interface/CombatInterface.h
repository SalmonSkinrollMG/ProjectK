﻿// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTK_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int GetPlayerLevel() const;

	virtual FVector GetCombatSocketVector() const;

	virtual void Die() = 0;

	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void UpdateWarpTarget(const FVector& WarpTarget);

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	UAnimMontage* GetHitAnimMontage();
};
