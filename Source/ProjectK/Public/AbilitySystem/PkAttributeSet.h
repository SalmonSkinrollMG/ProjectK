// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PkAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/*
	 *TBaseStaticDelegateInstance<FGameplayAttribute() , FDefaultDelegateUserPolicy()>::FFuncPtr FunctionPointer;
	 *Check DECLARE_DELEGATE_RETVAL
*/
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T , FDefaultDelegateUserPolicy>::FFuncPtr;

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() = default;

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	AActor* SourceActor = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;
	
};

UCLASS()
class PROJECTK_API UPkAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPkAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void ShowFloatingText(const FEffectProperties& EffectProperties, const float& LocalDamage , bool bCriticalHit) const;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	//---------------------------------------------Attributes----------------------------------------------//

	/*
	 * Meta Attributes (Progression)
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level, Category = "Progression")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Level);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Experience, Category = "Progression")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Experience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExperienceToNextLevel, Category = "Progression")
	FGameplayAttributeData ExperienceToNextLevel;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, ExperienceToNextLevel);


	
	/*
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "Primary Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Attack);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Primary Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Speed, Category = "Primary Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Speed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Primary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "Primary Attributes")
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, BaseDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Primary Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Primary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EnergyRecharge, Category = "Primary Attributes")
	FGameplayAttributeData EnergyRecharge;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, EnergyRecharge);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ElementalResistance, Category = "Primary Attributes")
	FGameplayAttributeData ElementalResistance;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, ElementalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, PhysicalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resolve, Category = "Primary Attributes")
	FGameplayAttributeData Resolve;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Resolve);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxResolve, Category = "Primary Attributes")
	FGameplayAttributeData MaxResolve;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, MaxResolve);


	/*
	 * Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritRate, Category = "Secondary Attributes")
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, CritRate);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, CritDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SkillDamage, Category = "Secondary Attributes")
	FGameplayAttributeData SkillDamage;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, SkillDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_UltimateDamage, Category = "Secondary Attributes")
	FGameplayAttributeData UltimateDamage;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, UltimateDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SkillDuration, Category = "Secondary Attributes")
	FGameplayAttributeData SkillDuration;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, SkillDuration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealingBonus, Category = "Secondary Attributes")
	FGameplayAttributeData HealingBonus;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, HealingBonus);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ShieldBonus, Category = "Secondary Attributes")
	FGameplayAttributeData ShieldBonus;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, ShieldBonus);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Secondary Attributes")
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, CooldownReduction);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageReduction, Category = "Secondary Attributes")
	FGameplayAttributeData DamageReduction;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, DamageReduction);

	

	/*
	 * Vital Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, MaxHealth);
	
	/*
	 * Internal / Temporary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Internal")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UPkAttributeSet, IncomingDamage);


	

	//---------------------------------------------OnReps----------------------------------------------//

	//Meta
	UFUNCTION() void OnRep_Level(const FGameplayAttributeData& OldLevel) const;
	UFUNCTION() void OnRep_Experience(const FGameplayAttributeData& OldExperience) const;
	UFUNCTION() void OnRep_ExperienceToNextLevel(const FGameplayAttributeData& OldExpToNext) const;
	
	// Primary
	UFUNCTION() void OnRep_Attack(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_Defense(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_Speed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_BaseDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_EnergyRecharge(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_ElementalResistance(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_PhysicalResistance(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_Resolve(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_MaxResolve(const FGameplayAttributeData& OldValue) const;

	// Secondary
	UFUNCTION() void OnRep_CritRate(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_CritDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_SkillDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_UltimateDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_SkillDuration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_HealingBonus(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_ShieldBonus(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_CooldownReduction(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_DamageReduction(const FGameplayAttributeData& OldValue) const;

	// Vital
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	//-----------------------------------Helpers-------------------------------------------------
	
	TMap<FGameplayTag , TStaticFuncPtr<FGameplayAttribute()>> TagToAttributeMap;
	
private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data , FEffectProperties& Properties);
};
