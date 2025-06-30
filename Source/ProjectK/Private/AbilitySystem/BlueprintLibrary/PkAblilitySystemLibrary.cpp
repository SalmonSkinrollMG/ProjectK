// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"
#include "UI/WidgetController/PKWidgetController.h"
#include "Controller/Player/PKPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PKPlayerState.h"
#include "UI/Hud/PKHud.h"

UOverlayWidgetController* UPkAblilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContext)
{
	if (APKPlayerController* PC = Cast<APKPlayerController>(UGameplayStatics::GetPlayerController(WorldContext,0)))
	{
		if (APKHud* HUD = Cast<APKHud>(PC->GetHUD()))
		{
			APKPlayerState* PS = PC->GetPlayerState<APKPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC , PS ,ASC , AS);
			return HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UPkAblilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContext)
{
	if (APKPlayerController* PC = Cast<APKPlayerController>(UGameplayStatics::GetPlayerController(WorldContext,0)))
	{
		if (APKHud* HUD = Cast<APKHud>(PC->GetHUD()))
		{
			APKPlayerState* PS = PC->GetPlayerState<APKPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC , PS ,ASC , AS);
			return HUD->GetAttributeWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
