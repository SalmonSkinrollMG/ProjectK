// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Meele,
	Ranged
};


USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly , Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
};
UCLASS()
class PROJECTK_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly , Category="CharacterDefaults | ClassDefaults")
	TMap<ECharacterClass , FCharacterClassDefaultInfo> CharacterClassDefaultMap;

	UPROPERTY(EditDefaultsOnly , Category="CharacterDefaults | CommonDefaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly , Category="CharacterDefaults | CommonDefaults")
	TSubclassOf<UGameplayEffect> MetaAttributes;

	UPROPERTY(EditDefaultsOnly , Category="CharacterDefaults | CommonDefaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass Class) const;
};
