// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PKWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC , APlayerState* PS , UAbilitySystemComponent* ASC , UAttributeSet* AS)
	: PlayerController(PC),
	PlayerState(PS),
	AbilitySystemComponent(ASC),
	AttributeSet(AS)
	{}

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	APlayerController* PlayerController = nullptr;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	APlayerState* PlayerState = nullptr;	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UAttributeSet* AttributeSet = nullptr;
};
UCLASS()
class PROJECTK_API UPKWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	UFUNCTION(BlueprintCallable)
	virtual  void BindCallbacksToDependencies();

protected:
	UPROPERTY(BlueprintReadOnly , Category = "Dependent classes")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly , Category = "Dependent classes")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly , Category = "Dependent classes")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly , Category = "Dependent classes")
	TObjectPtr<UAttributeSet> AttributeSet;
};
