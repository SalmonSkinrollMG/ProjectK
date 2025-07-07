// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PkAblilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class PROJECTK_API UPkAblilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure , Category="Ability System Library | Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(UObject* WorldContext);

	UFUNCTION(BlueprintPure , Category="Ability System Library | Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(UObject* WorldContext);

	UFUNCTION(BlueprintCallable , Category="Ability System Library | Default Attributes")
	static void InitializeDefaultAttributes(const UObject* WorldContext , ECharacterClass CharacterClass , float Level , UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable , Category="Ability System Library | Default Attributes")
	static void GiveStartupAbilities(const UObject* WorldContext , UAbilitySystemComponent* ASC);
};
