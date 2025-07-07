// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AbilitySystem/CharacterClassInfo.h"
#include "PKGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API APKGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly , Category="CharacterDefaults | ClassDefaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
