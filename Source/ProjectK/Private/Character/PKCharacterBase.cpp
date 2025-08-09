// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKCharacterBase.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectK/ProjectK.h"

APKCharacterBase::APKCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera , ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera , ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshMesh");
	WeaponMesh->SetupAttachment(GetMesh() , WeaponAttachmentSocket);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector APKCharacterBase::GetCombatSocketVector() const
{
	check(WeaponMesh);
	return WeaponMesh->GetSocketLocation(WeaponProjectileSocket);
}

void APKCharacterBase::Die()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true)); 
	HandleDeath();
}

void APKCharacterBase::HandleDeath_Implementation()
{
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APKCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APKCharacterBase::InitAbilityActorInfo()
{
}

void APKCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Attribute)
{
	check(GetAbilitySystemComponent());
	checkf(Attribute,TEXT("DefaultPrimaryAttribute is not a valid APKCharacterBase"));
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	EffectContextHandle.AddInstigator(this , this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Attribute , 1.0f , EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get() , GetAbilitySystemComponent());
}

void APKCharacterBase::AddCharacterAbilities()
{
	if (HasAuthority())
	{
		if (UPKAbilitySystemComponent* PkAbilitySystemComponent = Cast<UPKAbilitySystemComponent>(GetAbilitySystemComponent()))
		{
			PkAbilitySystemComponent->AddCharacterAbilites(StartupAbilities);
		}
	}
}

void APKCharacterBase::InitializeDefaultAttributes()
{
	
	/*
	 * Dependent attributes must be initialized first.
	 * Base Damage is dependent on Level , But Level is a meta Attribute.
	 * so initialize meta attributes first.
	 */
	ApplyEffectToSelf(DefaultMetaAttribute);
	ApplyEffectToSelf(DefaultPrimaryAttribute);
	ApplyEffectToSelf(DefaultSecondaryAttribute);
}
