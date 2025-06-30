// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/PKAbilitySystemComponent.h"
#include "AbilitySystem/PkAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (UPkAttributeSet* PKAttributeSet = Cast<UPkAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(PKAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(PKAttributeSet->GetMaxHealth());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (UPkAttributeSet* PKAttributeSet = Cast<UPkAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PKAttributeSet->GetHealthAttribute()).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PKAttributeSet->GetMaxHealthAttribute()).AddWeakLambda(this, [this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	}
	if (AbilitySystemComponent)
	{
		Cast<UPKAbilitySystemComponent>(AbilitySystemComponent)->OnEffectApplied.AddWeakLambda(
			this,[this] (const FGameplayTagContainer& GameplayTags)
			{
				for (FGameplayTag GameplayTag : GameplayTags)
				{
					/*FString TagName = GameplayTag.ToString();
					GEngine->AddOnScreenDebugMessage(
						-1,                            
						5.0f,                          
						FColor::Cyan,              
						FString::Printf(TEXT("Tag: %s"), *TagName)	);*/

					//Broadcasting Message tags to all the widgets owned by this widget controller.
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (GameplayTag.MatchesTag(MessageTag))
					{
						FUIWidgetRow* Row = GetTableRowByTag<FUIWidgetRow>(MessageDataTable , GameplayTag);
						OnMessageUIWidget.Broadcast(*Row);
					}
				}
			}
		);
	}
	
}