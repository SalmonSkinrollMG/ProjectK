// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKEnemeyCharacter.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"
#include "AI/PKAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	//Controller setup
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	

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

void APKEnemeyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority())
	{
		return;
	}
	PKAIController = Cast<APKAIController>(NewController);
	PKAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	PKAIController->RunBehaviorTree(BehaviorTree);
	PKAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsHitReacting"), false);
	if (CharacterClass != ECharacterClass::Meele)
	{
		PKAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsRangedCharacter"), true);
	}
}

void APKEnemeyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile , ECR_Overlap);
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
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddUObject(this , &ThisClass::OnHealthUpdated);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddUObject(this , &ThisClass::OnMaxHealthUpdated);

	AbilitySystemComponent->RegisterGameplayTagEvent(FPKGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
	this,
	&APKEnemeyCharacter::OnHitReactTagAdded
	);
	
}

void APKEnemeyCharacter::OnHitReactTagAdded(const FGameplayTag IncomingTag, int32 count)
{
	bHitReacting = count > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.0f : BaseWalkSpeed;
	PKAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsHitReacting"), bHitReacting);
}

void APKEnemeyCharacter::HandleDeath()
{
	HealthBarWidget->DestroyComponent();
	Super::HandleDeath();
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

void APKEnemeyCharacter::OnHealthUpdated(const FOnAttributeChangeData& Data) const
{
	OnHealthAttributeUpdated.Broadcast(Data.NewValue);
}

void APKEnemeyCharacter::OnMaxHealthUpdated(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthAttributeUpdated.Broadcast(Data.NewValue);
}

void APKEnemeyCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this , this);
	Cast<UPKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}


void APKEnemeyCharacter::InitializeDefaultAttributes()
{
	UPkAblilitySystemLibrary::InitializeDefaultAttributes(GetWorld() , CharacterClass , Level , AbilitySystemComponent);
}