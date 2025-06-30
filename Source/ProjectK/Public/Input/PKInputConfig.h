// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PKInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FPKInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class PROJECTK_API UPKInputConfig : public UDataAsset
{
	GENERATED_BODY()

	public:

	const UInputAction* FindInputActionForTag(const FGameplayTag TagToFind) const;
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TArray<FPKInputActions> InputActions;
};
