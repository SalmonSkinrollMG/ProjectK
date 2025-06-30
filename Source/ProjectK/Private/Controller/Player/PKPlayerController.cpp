// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Controller/Player/PKPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/BlueprintLibrary/PkAblilitySystemLibrary.h"
#include "Components/SplineComponent.h"
#include "Input/PKEnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"
#include "Misc/PKGameplayTags.h"

APKPlayerController::APKPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineConponent"));
}

void APKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MappingContext);

	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
    {
    	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    	{
    		InputSystem->AddMappingContext(MappingContext, 0);
    	}
    }

	//Mouse input behaviour

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	
}

void APKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UPKEnhancedInputComponent* PKEnhancedInputComponent = CastChecked<UPKEnhancedInputComponent>(InputComponent);

	PKEnhancedInputComponent->BindAction(MoveAction , ETriggerEvent::Triggered , this , &APKPlayerController::Move);

	PKEnhancedInputComponent->BindAbilityActions(InputConfig, this,
		&APKPlayerController::AbilityInputPressed,
		&APKPlayerController::AbilityInputReleased,
		&APKPlayerController::AbilityInputHeld);
	
}

UPKAbilitySystemComponent* APKPlayerController::GetAbilitySystemComponent()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UPKAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AbilitySystemComponent;
}

void APKPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation() , ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline , ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void APKPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	HitUnderCursor();
	AutoRun();
}

void APKPlayerController::Move(const FInputActionValue& InputValue)
{
	const FVector2D InputVector= InputValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotator{0.0f , Rotation.Yaw , 0.0f};
	
	const FVector ForwardVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	if(APawn* PossessedPawn = GetPawn())
	{
		PossessedPawn->AddMovementInput(ForwardVector , InputVector.Y);
		PossessedPawn->AddMovementInput(RightVector , InputVector.X);
	}
}

void APKPlayerController::HighlightActors(const FHitResult& HitResult)
{
	PreviousActor = CurrentActor;
	CurrentActor = HitResult.GetActor();

	if (PreviousActor && PreviousActor != CurrentActor)
	{
		PreviousActor->UnHighlightActor();
	}

	if (CurrentActor && PreviousActor != CurrentActor)
	{
		CurrentActor->HighlightActor();
	}
}

void APKPlayerController::HitUnderCursor()
{
	GetHitResultUnderCursor(ECC_Visibility , false , CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}
	
	HighlightActors(CursorHit);	
}

void APKPlayerController::AbilityInputPressed(FGameplayTag Tag)
{
	if (Tag.MatchesTagExact(FPKGameplayTags::Get().InputTag_Key_LMB))
	{
		bTargeting = CurrentActor ? true : false;
		bAutoRunning = false;
	}
}

void APKPlayerController::AbilityInputReleased(FGameplayTag Tag)
{
	if (!Tag.MatchesTagExact(FPKGameplayTags::Get().InputTag_Key_LMB))
	{
		if (GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagHeld(Tag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagHeld(Tag);
		}
	}
	else
	{
		const APawn* ControlledPawn = GetPawn();
		if (ControlledPawn && FollowTime <= ShortPressedThreshold)
		{
			if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this , ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector NavPoint : NavigationPath->PathPoints)
				{
					Spline->AddSplinePoint(NavPoint , ESplineCoordinateSpace::World);
					//DrawDebugSphere(GetWorld() , NavPoint , 3 , 10 , FColor::Purple , false , 5.0f);
				}
				CachedDestination = NavigationPath->PathPoints.Last();
				bAutoRunning = true;
			}
		}
		FollowTime = false;
		bTargeting = false;
	}
}

void APKPlayerController::AbilityInputHeld(const FGameplayTag Tag)
{
	if (!Tag.MatchesTagExact(FPKGameplayTags::Get().InputTag_Key_LMB))
	{
		if (GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagHeld(Tag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagHeld(Tag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}
