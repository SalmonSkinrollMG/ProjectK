// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PKWidgetController.h"
#include "OverlayWidgetController.generated.h"


class UPKUserWidget;
struct FOnAttributeChangeData;


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag GameplayTag = FGameplayTag();

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<UPKUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	UTexture2D* MessageTexture;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature , FUIWidgetRow , Row);



UCLASS(Blueprintable , BlueprintType)
class PROJECTK_API UOverlayWidgetController : public UPKWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	template <class T>
	T* GetTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	UPROPERTY(BlueprintAssignable, Category = "GAS Events")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS Events")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS Events")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS Events")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "UI message")
	FMessageWidgetRowSignature OnMessageUIWidget;

protected:
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category="Widget Data Table")
	TObjectPtr<UDataTable> MessageDataTable;
	

	template<typename T>
	T* GetTableRowByTag(UDataTable& DataTable , const FGameplayTag Tag);
};


template <typename T>
T* UOverlayWidgetController::GetTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	T* Row = DataTable->FindRow<T>(Tag.GetTagName() , TEXT(""));
	return Row;
}


