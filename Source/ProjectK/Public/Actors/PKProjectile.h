// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "PKProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class PROJECTK_API APKProjectile : public AActor
{
	GENERATED_BODY()

public:
	APKProjectile();
	void Destroyed() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float InitialSpeed = 550.0f;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float MaxSpeed = 550.0f;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float ProjectileGravityScale = 0.0f;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float ProjectileLifeSpan = 15.0f;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle EffectSpecHandle;

protected:

	virtual void BeginPlay() override;
	void SpawnFXatLocation();

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere , Category = "ProjectileEffects")
	TObjectPtr<UNiagaraSystem> HitVFX;

	UPROPERTY(EditAnywhere , Category = "ProjectileEffects")
	TObjectPtr<USoundBase> HitSFX;

	UPROPERTY(EditAnywhere , Category = "ProjectileEffects")
	TObjectPtr<USoundBase> ProjectileHissSFX;

	TObjectPtr<UAudioComponent> AudioComponent;
	bool bHit = false;
};
