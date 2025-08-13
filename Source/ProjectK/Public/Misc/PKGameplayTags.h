// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton for storing GameplayTags.
 */
struct FPKGameplayTags
{
public:
	
	// ----------------- Meta / Progression Attributes -----------------
	FGameplayTag Attribute_Meta_Level;
	FGameplayTag Attribute_Meta_Experience;
	FGameplayTag Attribute_Meta_ExperienceToNextLevel;
	
	// ----------------- Primary Attributes -----------------
	FGameplayTag Attribute_Primary_HP;
	FGameplayTag Attribute_Primary_MaxHealth;
	FGameplayTag Attribute_Primary_Attack;
	FGameplayTag Attribute_Primary_Defense;
	FGameplayTag Attribute_Primary_Speed;
	FGameplayTag Attribute_Primary_AttackSpeed;
	FGameplayTag Attribute_Primary_Stamina;
	FGameplayTag Attribute_Primary_EnergyRecharge;
	FGameplayTag Attribute_Primary_ElementalResistance;
	FGameplayTag Attribute_Primary_PhysicalResistance;
	FGameplayTag Attribute_Primary_ResolveCost;

	// ----------------- Secondary Attributes -----------------
	FGameplayTag Attribute_Secondary_CritRate;
	FGameplayTag Attribute_Secondary_CritDamage;
	FGameplayTag Attribute_Secondary_SkillDamage;
	FGameplayTag Attribute_Secondary_UltimateDamage;
	FGameplayTag Attribute_Secondary_SkillDuration;
	FGameplayTag Attribute_Secondary_HealingBonus;
	FGameplayTag Attribute_Secondary_ShieldBonus;
	FGameplayTag Attribute_Secondary_CooldownReduction;
	FGameplayTag Attribute_Secondary_DamageReduction;

	// --------------------------- Input Tags ---------------------------

	//Keyboard
	FGameplayTag InputTag_Key_RMB;
	FGameplayTag InputTag_Key_LMB;
	FGameplayTag InputTag_Key_NUM_1;
	FGameplayTag InputTag_Key_NUM_2;
	FGameplayTag InputTag_Key_NUM_3;
	FGameplayTag InputTag_Key_NUM_4;

	// --------------------------- Damage Tags ---------------------------
	FGameplayTag Damage;
	FGameplayTag Damage_ElementalDamage;
	FGameplayTag Damage_PhysicalDamage;
	
	
	TMap<FGameplayTag , FGameplayTag> DamageTypesToResistanceMap;

	//-----------------------------Effects Tags ----------------------------
	FGameplayTag Effects_HitReact;
	

	static const FPKGameplayTags& Get() {return Instance;}
	static void InitializeNativeGameplayTags();
protected:
	static FPKGameplayTags	Instance;
};
