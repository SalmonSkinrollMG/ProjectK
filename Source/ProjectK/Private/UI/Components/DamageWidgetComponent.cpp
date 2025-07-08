// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/Components/DamageWidgetComponent.h"


// Sets default values for this component's properties
UDamageWidgetComponent::UDamageWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

