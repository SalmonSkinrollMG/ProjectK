// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKEnemeyCharacter.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "ProjectK/ProjectK.h"
#include "UI/Widgets/PKUserWidget.h"

APKEnemeyCharacter::APKEnemeyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->CustomDepthStencilValue = 250; // refer PP_Material for enemy Outline.
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile , ECR_Overlap);
	AbilitySystemComponent = CreateDefaultSubobject<UPKAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	
	AttributeSet = CreateDefaultSubobject<UPkAttributeSet>("AttributeSet");
}


void APKEnemeyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	/*
	 * For enemies , the Widget controller is self
	 * Enemies will directly broadcast to its widgets to update the attribute HUD.
	 */
	if (UPKUserWidget* Widget = Cast<UPKUserWidget>(HealthBarWidget->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
	}
	UPkAttributeSet* AS = Cast<UPkAttributeSet>(AttributeSet);
	OnHealthAttributeUpdated.Broadcast(AS->GetHealth());
	OnMaxHealthAttributeUpdated.Broadcast(AS->GetMaxHealth());
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddWeakLambda(this,
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthAttributeUpdated.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddWeakLambda(this,
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthAttributeUpdated.Broadcast(Data.NewValue);
		}
	);
	
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
	InitializeDefaultAttributes();
}

