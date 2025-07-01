// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "PKPlayerController.generated.h"


class USplineComponent;
class UPKAbilitySystemComponent;
class UPKInputConfig;
class IEnemyInterface;
class UInputMappingContext;
class UInputAction;


UCLASS()
class PROJECTK_API APKPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APKPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere , Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void Move(const FInputActionValue& InputValue);
	void HighlightActors(const FHitResult& HitResult);
	void HitUnderCursor();
	FHitResult CursorHit;

	TScriptInterface<IEnemyInterface> PreviousActor;
	TScriptInterface<IEnemyInterface> CurrentActor;

	void AbilityInputPressed(FGameplayTag Tag);
	void AbilityInputReleased(FGameplayTag Tag);
	void AbilityInputHeld(FGameplayTag Tag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UPKInputConfig> InputConfig;

	UFUNCTION(BlueprintCallable)
	UPKAbilitySystemComponent* GetAbilitySystemComponent();
	

	TObjectPtr<UPKAbilitySystemComponent> AbilitySystemComponent;
	
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.0f;
	float ShortPressedThreshold = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.0f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
	
	
	bool bTargeting = false;
	bool bAutoRunning = false;


	void ShiftKeyPressed(){ bShiftKeyPressed = true; }
	void ShiftKeyReleased(){ bShiftKeyPressed = false; }
	bool bShiftKeyPressed = false;
};


