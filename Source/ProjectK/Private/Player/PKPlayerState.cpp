// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Player/PKPlayerState.h"

#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "Net/UnrealNetwork.h"

APKPlayerState::APKPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPKAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UPkAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.0f);
}

void APKPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

