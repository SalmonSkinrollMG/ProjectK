// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "UI/WidgetController/PKWidgetController.h"
#include "Controller/Player/PKPlayerController.h"
#include "Game/PKGameMode.h"
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

void UPkAblilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContext, ECharacterClass CharacterClass,
	float Level, UAbilitySystemComponent* ASC)
{
	const APKGameMode* PKGameMode = Cast<APKGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if (PKGameMode == nullptr)
	{
		return;
	}

	UCharacterClassInfo* CharacterClassInfo = PKGameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	AActor* Owner = ASC->GetAvatarActor();
	EffectContextHandle.AddSourceObject(Owner);
	
	
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level , EffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level , EffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle MetaAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->MetaAttributes, Level , EffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*MetaAttributeSpecHandle.Data.Get());
}
