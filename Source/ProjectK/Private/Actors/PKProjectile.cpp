// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Actors/PKProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectK/ProjectK.h"


APKProjectile::APKProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic , ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic , ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileComponent->InitialSpeed = InitialSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	ProjectileComponent->ProjectileGravityScale = ProjectileGravityScale;
}

void APKProjectile::Destroyed()
{
	if (!HasAuthority())
	{
		if (bHit )
		{
			SpawnFXatLocation();
		}
		if (IsValid(AudioComponent))
		{
			AudioComponent->Stop();
		}
	}
	Super::Destroyed();
}


void APKProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(ProjectileLifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APKProjectile::OnSphereOverlap);
	if (!HasAuthority())
	{
		checkf(ProjectileHissSFX , TEXT("Projectile hiss sfx is not assigned"))
		AudioComponent = UGameplayStatics::SpawnSoundAttached(ProjectileHissSFX , GetRootComponent());
	}
}

void APKProjectile::SpawnFXatLocation() const
{
	UGameplayStatics::PlaySoundAtLocation(this , HitSFX , GetActorLocation() , FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this , HitVFX , GetActorLocation());
}

void APKProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnFXatLocation();
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
	else
	{
		bHit = true;
	}
	Destroy();
}


