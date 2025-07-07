// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKEnemeyCharacter.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Misc/PKGameplayTags.h"
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


UAnimMontage* APKEnemeyCharacter::GetHitAnimMontage_Implementation()
{
	return HitReactMontage;
}

void APKEnemeyCharacter::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void APKEnemeyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();

	UPkAblilitySystemLibrary::GiveStartupAbilities(this , AbilitySystemComponent);

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

	AbilitySystemComponent->RegisterGameplayTagEvent(FPKGameplayTags::Get().Internal_Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
	this,
	&APKEnemeyCharacter::OnHitReactTagAdded
	);
	
}

void APKEnemeyCharacter::OnHitReactTagAdded(const FGameplayTag IncomingTag, int32 count)
{
	bHitReacting = count > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.0f : BaseWalkSpeed;
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

