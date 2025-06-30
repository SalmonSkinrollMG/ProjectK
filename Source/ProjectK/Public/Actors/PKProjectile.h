// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PKProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class PROJECTK_API APKProjectile : public AActor
{
	GENERATED_BODY()

public:
	APKProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileComponent;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float InitialSpeed = 550.0f;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float MaxSpeed = 550.0f;

	UPROPERTY(EditDefaultsOnly , Category = "ProjectileProperties")
	float ProjectileGravityScale = 0.0f;

protected:

	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
