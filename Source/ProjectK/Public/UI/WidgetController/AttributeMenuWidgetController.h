// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PKWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UPkAttributeInfoAsset;
struct FPKAttributeinfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FPKAttributeinfo& , Info);

UCLASS(BlueprintType , Blueprintable)
class PROJECTK_API UAttributeMenuWidgetController : public UPKWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues()override;

	virtual  void BindCallbacksToDependencies()override;

	UPROPERTY(BlueprintAssignable , Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;


protected:
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UPkAttributeInfoAsset> AttributeInfo;
};
