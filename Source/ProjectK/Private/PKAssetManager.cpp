// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "PKAssetManager.h"
#include "Misc/PKGameplayTags.h"

UPKAssetManager& UPKAssetManager::Get()
{
	checkf(GEngine , TEXT("GEngine not initialized"));

	UPKAssetManager* AssetManager = Cast<UPKAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UPKAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FPKGameplayTags::InitializeNativeGameplayTags();
}
