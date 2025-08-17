// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "PKEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplyPolicy : uint8
{
	None UMETA(DisplayName = "None"),
	ApplyOnOverlap UMETA(DisplayName = "ApplyOnOverlap"),
	ApplyOnEndOverlap UMETA(DisplayName = "ApplyOnEndOverlap"),
	DoNotApply UMETA(DisplayName = "DoNotOverlap"),
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	None UMETA(DisplayName = "None"),
	RemoveOnEndOverlap UMETA(DisplayName = "RemoveOnEndOverlap"),
	DoNotRemove UMETA(DisplayName = "DoNotOverlap"),
};

UCLASS()
class PROJECTK_API APKEffectActor : public AActor
{
	GENERATED_BODY()

public:
	APKEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTarget(AActor* TargetActor , TSubclassOf<UGameplayEffect> InGameplayEffect);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	
	/*
	 *Currently Not using
	 */
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Effect Properties")
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Effect Properties")
	bool bCanAffectEnemies = false;

	// Infinite
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Infinite")
	EEffectApplyPolicy InfiniteGameplayApplyPolicy = EEffectApplyPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Infinite")
	EEffectRemovalPolicy InfiniteGameplayRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	
	// Instant
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Instant")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Instant")
	EEffectApplyPolicy InstantGameplayApplyPolicy = EEffectApplyPolicy::DoNotApply;

	//Removes instantly

	// Duration
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Duration")
	TSubclassOf<UGameplayEffect> DurationGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect Properties | Duration")
	EEffectApplyPolicy DurationGameplayApplyPolicy = EEffectApplyPolicy::DoNotApply;

	//Removes after duration

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="Effect Properties")
	int EffectLevel = 1;
	
	//////////////////////////
	UPROPERTY()
	TMap<UAbilitySystemComponent* ,FActiveGameplayEffectHandle> ActiveGameplayEffects;
};
