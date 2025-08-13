// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/PkAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"
#include "Controller/Player/PKPlayerController.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PKGameplayTags.h"
#include "Net/UnrealNetwork.h"

UPkAttributeSet::UPkAttributeSet()
{
	const FPKGameplayTags GameplayTags = FPKGameplayTags::Get();
	// ----------------- Meta -----------------
	TagToAttributeMap.Add(GameplayTags.Attribute_Meta_Level, GetLevelAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Meta_Experience, GetExperienceAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Meta_ExperienceToNextLevel, GetExperienceToNextLevelAttribute);
	// ----------------- Primary -----------------
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_HP, GetHealthAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_MaxHealth, GetMaxHealthAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_Attack, GetAttackAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_Defense, GetDefenseAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_Speed, GetSpeedAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_AttackSpeed, GetAttackSpeedAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_Stamina, GetStaminaAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_EnergyRecharge, GetEnergyRechargeAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_ElementalResistance, GetElementalResistanceAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_PhysicalResistance, GetPhysicalResistanceAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Primary_ResolveCost, GetResolveAttribute);

	// ----------------- Secondary -----------------
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_CritRate, GetCritRateAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_CritDamage, GetCritDamageAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_SkillDamage, GetSkillDamageAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_UltimateDamage, GetUltimateDamageAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_SkillDuration, GetSkillDurationAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_HealingBonus, GetHealingBonusAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_ShieldBonus, GetShieldBonusAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_CooldownReduction, GetCooldownReductionAttribute);
	TagToAttributeMap.Add(GameplayTags.Attribute_Secondary_DamageReduction, GetDamageReductionAttribute);
}

void UPkAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Meta
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Experience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, ExperienceToNextLevel, COND_None, REPNOTIFY_Always);
	
	// Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, EnergyRecharge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, ElementalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Resolve, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, MaxResolve, COND_None, REPNOTIFY_Always);

	// Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, SkillDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, UltimateDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, SkillDuration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, HealingBonus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, ShieldBonus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, DamageReduction, COND_None, REPNOTIFY_Always);

	// Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPkAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UPkAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UPkAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// Safe handle for gameplay tags, instigator, target, etc.
	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		float LocalDamage = Data.EvaluatedData.Magnitude;
		SetIncomingDamage(0);
		if (LocalDamage > 0.0f)
		{
			const float NewHealth = GetHealth() - LocalDamage;
			SetHealth(FMath::Clamp(NewHealth , 0.0f , GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.0f;

			if (bFatal)
			{
				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(EffectProperties.TargetActor))
				{
					 CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FPKGameplayTags::Get().Effects_HitReact);
				EffectProperties.TargetAbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
			}
			const bool bCriticalHit = UPkAblilitySystemLibrary::IsCriticalHit(EffectProperties.EffectContextHandle);
			ShowFloatingText(EffectProperties, LocalDamage, bCriticalHit );
		}
	}

	UE_LOG(LogTemp , Warning , TEXT("Health for %s is reduced to %f"),*EffectProperties.TargetActor->GetName(),GetHealth());
}

void UPkAttributeSet::ShowFloatingText(const FEffectProperties& EffectProperties, const float& LocalDamage, bool bCriticalHit) const
{
	//Ignoring Self damage
	if (EffectProperties.SourceCharacter != EffectProperties.TargetCharacter)
	{
		/*
		 *For Damage text only for Source , Get EFeectProperties.SourceCharacter->GetController();
		 */
		
		//Showing damage Numbers for all the player controller in the game . So both the players would be able to see the damage number
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (auto PC = Cast<APKPlayerController>(It->Get()))
			{
				PC->ShowDamageOnClient(LocalDamage, EffectProperties.TargetCharacter , bCriticalHit);
			}
		}
	}
}

// ------------------------ OnRep Functions ------------------------ //
void UPkAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Level, OldValue);
}

void UPkAttributeSet::OnRep_Experience(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Experience, OldValue);
}

void UPkAttributeSet::OnRep_ExperienceToNextLevel(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, ExperienceToNextLevel, OldValue);
}

void UPkAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Attack, OldValue);
}
void UPkAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Defense, OldValue);
}
void UPkAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Speed, OldValue);
}
void UPkAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, AttackSpeed, OldValue);
}
void UPkAttributeSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, BaseDamage, OldValue);
}
void UPkAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Stamina, OldValue);
}
void UPkAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, MaxStamina, OldValue);
}
void UPkAttributeSet::OnRep_EnergyRecharge(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, EnergyRecharge, OldValue);
}
void UPkAttributeSet::OnRep_ElementalResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, ElementalResistance, OldValue);
}
void UPkAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, PhysicalResistance, OldValue);
}
void UPkAttributeSet::OnRep_Resolve(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Resolve, OldValue);
}
void UPkAttributeSet::OnRep_MaxResolve(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, MaxResolve, OldValue);
}

void UPkAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, CritRate, OldValue);
}
void UPkAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, CritDamage, OldValue);
}
void UPkAttributeSet::OnRep_SkillDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, SkillDamage, OldValue);
}
void UPkAttributeSet::OnRep_UltimateDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, UltimateDamage, OldValue);
}
void UPkAttributeSet::OnRep_SkillDuration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, SkillDuration, OldValue);
}
void UPkAttributeSet::OnRep_HealingBonus(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, HealingBonus, OldValue);
}
void UPkAttributeSet::OnRep_ShieldBonus(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, ShieldBonus, OldValue);
}
void UPkAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, CooldownReduction, OldValue);
}
void UPkAttributeSet::OnRep_DamageReduction(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, DamageReduction, OldValue);
}

void UPkAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, Health, OldValue);
}
void UPkAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPkAttributeSet, MaxHealth, OldValue);
}



void UPkAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data , FEffectProperties& Properties)
{
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	Properties.SourceAbilitySystemComponent = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();


	if (IsValid(Properties.SourceAbilitySystemComponent) &&
		Properties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() &&
		Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.SourceActor = Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Properties.SourceController = Properties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (Properties.SourceController == nullptr && Properties.SourceActor != nullptr)
		{
			if (APawn* SourcePawn = Cast<APawn>(Properties.SourceActor))
			{
				Properties.SourceController = SourcePawn->GetController();
			}
		}
		if (Properties.SourceController)
		{
			Properties.SourceCharacter = Properties.SourceController->GetCharacter();
		}
				
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetActor);
		Properties.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetActor);
	}
}
