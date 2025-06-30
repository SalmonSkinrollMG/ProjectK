// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/Data/PkAttributeInfoAsset.h"
#include "AbilitySystem/PkAttributeSet.h"
#include "Misc/PKGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UPkAttributeSet* AS = CastChecked<UPkAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto Pair : AS->TagToAttributeMap)
	{
		FPKAttributeinfo Info = AttributeInfo->GetAttributesInfo(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UPkAttributeSet* AS = CastChecked<UPkAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagToAttributeMap)
	{
		FGameplayAttribute Attribute = Pair.Value();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddWeakLambda(this,
			[this, Pair, Attribute, AS](const FOnAttributeChangeData& Data)
			{
				FPKAttributeinfo Info = AttributeInfo->GetAttributesInfo(Pair.Key);
				Info.AttributeValue = Attribute.GetNumericValue(AS);
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}


}
