// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.
// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "PKCharacterBase.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;
class UAnimMontage;

UCLASS(abstract)
class PROJECTK_API APKCharacterBase : public ACharacter , public IAbilitySystemInterface , public ICombatInterface
{
	GENERATED_BODY()

public:
	APKCharacterBase();

	virtual void InitAbilityActorInfo();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	virtual UAttributeSet* GetAttributeSet() const{return  AttributeSet;}

	UPROPERTY(BlueprintReadWrite , EditAnywhere , Category="Combat")
	TObjectPtr<USkeletalMeshComponent>	WeaponMesh;
	
	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="Combat")
	FName WeaponAttachmentSocket = "WeaponSocket";

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="Combat")
	FName WeaponProjectileSocket = "WeaponProjectileSocket";

	virtual FVector GetCombatSocketVector() const override;

	virtual void Die() override;

	UFUNCTION(NetMulticast , Reliable)
	virtual void HandleDeath();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category= "GamePlayAbilitySystem|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category= "GamePlayAbilitySystem|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category= "GamePlayAbilitySystem|Attributes")
	TSubclassOf<UGameplayEffect> DefaultMetaAttribute;


	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category= "Animation | Montages")
	UAnimMontage* HitReactMontage;

	UFUNCTION(BlueprintCallable)
	virtual void InitializeDefaultAttributes();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttribute);

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category= "GamePlayAbilitySystem|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	void AddCharacterAbilities();
};
