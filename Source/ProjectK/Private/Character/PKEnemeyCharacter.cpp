// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKEnemeyCharacter.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"

APKEnemeyCharacter::APKEnemeyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->CustomDepthStencilValue = 250; // refer PP_Material for enemy Outline.

	AbilitySystemComponent = CreateDefaultSubobject<UPKAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UPkAttributeSet>("AttributeSet");
}


void APKEnemeyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void APKEnemeyCharacter::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
}

void APKEnemeyCharacter::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void APKEnemeyCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this , this);
	Cast<UPKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

