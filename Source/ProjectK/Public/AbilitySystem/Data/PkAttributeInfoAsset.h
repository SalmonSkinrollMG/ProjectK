// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PkAttributeInfoAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPKAttributeinfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDesc;

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.0f;

	
};

UCLASS()
class PROJECTK_API UPkAttributeInfoAsset : public UDataAsset
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPKAttributeinfo> AbilityInformation;

/*
 * Send Tag to find and reference to a bool
 * bPrintNotFound = true : Prints Error if the tag is not found
 */
	UFUNCTION(BlueprintCallable)
	FPKAttributeinfo GetAttributesInfo(FGameplayTag Tag , bool bPrintNotFound = true);
};
