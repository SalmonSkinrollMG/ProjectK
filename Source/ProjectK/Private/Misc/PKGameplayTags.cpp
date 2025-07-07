// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Misc/PKGameplayTags.h"

#include "GameplayTagsManager.h"

FPKGameplayTags FPKGameplayTags::Instance;

void FPKGameplayTags::InitializeNativeGameplayTags()
{
	// ----------------- Meta / Progression Attributes -----------------
	Instance.Attribute_Meta_Level = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.Level"), TEXT("Character's current level"));
	Instance.Attribute_Meta_Experience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.Experience"), TEXT("Current experience points"));
	Instance.Attribute_Meta_ExperienceToNextLevel = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.ExperienceToNextLevel"), TEXT("XP required for next level"));
	
	// ----------------- Primary Attributes -----------------
 
	Instance.Attribute_Primary_HP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.HP"), TEXT("Character's Health Points"));

	Instance.Attribute_Primary_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Attack"), TEXT("Base attack power"));

	Instance.Attribute_Primary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Defense"), TEXT("Base defense value"));

	Instance.Attribute_Primary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Speed"), TEXT("Turn or movement speed"));

	Instance.Attribute_Primary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.AttackSpeed"), TEXT("Rate of basic attacks"));

	Instance.Attribute_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Stamina"), TEXT("Stamina used for dodging or sprinting"));

	Instance.Attribute_Primary_EnergyRecharge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.EnergyRecharge"), TEXT("Rate at which resolve/energy is regenerated"));

	Instance.Attribute_Primary_ElementalResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.ElementalResistance"), TEXT("Resistance against elemental damage"));

	Instance.Attribute_Primary_ResolveCost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.ResolveCost"), TEXT("Energy cost to use ultimate abilities"));

	// ----------------- Secondary Attributes -----------------

	
	Instance.Attribute_Secondary_CritRate = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.CritRate"), TEXT("Chance to inflict critical damage"));

	Instance.Attribute_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.CritDamage"), TEXT("Bonus damage multiplier for critical hits"));

	Instance.Attribute_Secondary_SkillDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.SkillDamage"), TEXT("Additional damage dealt by skills"));

	Instance.Attribute_Secondary_UltimateDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.UltimateDamage"), TEXT("Additional damage dealt by ultimate abilities"));

	Instance.Attribute_Secondary_SkillDuration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.SkillDuration"), TEXT("Extended duration for skills"));

	Instance.Attribute_Secondary_HealingBonus = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.HealingBonus"), TEXT("Bonus applied to all healing effects"));

	Instance.Attribute_Secondary_ShieldBonus = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.ShieldBonus"), TEXT("Bonus applied to generated shields"));

	Instance.Attribute_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.CooldownReduction"), TEXT("Reduces cooldowns of abilities"));

	Instance.Attribute_Secondary_DamageReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.DamageReduction"), TEXT("Reduces incoming damage"));

	// ----------------- Input Tags -----------------
	Instance.InputTag_Key_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.LMB"), TEXT("Left mouse Button input"));

	Instance.InputTag_Key_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.RMB"),TEXT("Right mouse Button input"));
	
	Instance.InputTag_Key_NUM_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.1") , TEXT("Number pad 1"));

	Instance.InputTag_Key_NUM_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.2") , TEXT("Number pad 2"));
	
	Instance.InputTag_Key_NUM_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.3") , TEXT("Number pad 3"));

	Instance.InputTag_Key_NUM_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Key.4") , TEXT("Number pad 4"));

	
	// ----------------- Internal Attributes (Not Replicated) -----------------
	Instance.Internal_IncomingDamage = UGameplayTagsManager::Get().AddNativeGameplayTag( 
		FName("Internal.IncomingDamage"), TEXT("Temporary value used to hold incoming damage during calculation."));

	// ----------------- Effects (Not Replicated) -----------------
	Instance.Internal_Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag( 
		FName("Internal.Effects.HitReact"), TEXT("Tag to grant the actor to during hit"));
}
