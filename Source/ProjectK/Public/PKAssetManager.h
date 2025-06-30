// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTK_API UPKAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UPKAssetManager& Get();

	virtual void StartInitialLoading() override;
};
