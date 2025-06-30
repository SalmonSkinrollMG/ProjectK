// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Actors/PKProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


APKProjectile::APKProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	
	/*
	 *TODO:Create a separate Profile for the projectile with the following Responses.
	 */
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic , ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic , ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileComponent->InitialSpeed = InitialSpeed;
	ProjectileComponent->MaxSpeed = MaxSpeed;
	ProjectileComponent->ProjectileGravityScale = ProjectileGravityScale;
}


void APKProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APKProjectile::OnSphereOverlap);
}

void APKProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


