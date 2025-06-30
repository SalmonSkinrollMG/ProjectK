// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Character/PKPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "Controller/Player/PKPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PKPlayerState.h"
#include "UI/Hud/PKHud.h"

APKPlayerCharacter::APKPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f , 400.0f , 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PrimaryActorTick.bCanEverTick = true;
}

void APKPlayerCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	if (APKPlayerState* PKPlayerState = GetPlayerState<APKPlayerState>())
	{
		PKPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PKPlayerState , this);
		AbilitySystemComponent = PKPlayerState->GetAbilitySystemComponent();
		/*
		 * This creates dependency on UPKAbilitySystemComponent
		 * PKAbilitySystemComponent should never have dependency on PkCharacters.
		 */
		Cast<UPKAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
		AttributeSet = PKPlayerState->GetAttributeSet();

		if (APKPlayerController* PKPlayerController = Cast<APKPlayerController>(GetController()))
		{
			if (APKHud* Hud = Cast<APKHud>(PKPlayerController->GetHUD()))
			{
				Hud->InitOverlay(PKPlayerController , PKPlayerState , AbilitySystemComponent , AttributeSet);
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		InitializeDefaultAttributes();
	});
}

void APKPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void APKPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}


void APKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


