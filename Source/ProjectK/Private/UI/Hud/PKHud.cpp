// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/Hud/PKHud.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/PKUserWidget.h"

UOverlayWidgetController* APKHud::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this , OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* APKHud::GetAttributeWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this , AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void APKHud::InitOverlay(APlayerController* PC , APlayerState* PS , UAbilitySystemComponent* ASC , UAttributeSet* AS)
{
	checkf(OverlayWidgetClass , TEXT("Overlay WidgetClass is uninitialized ,  fill PKHudClass"))
	checkf(OverlayWidgetControllerClass , TEXT("Overlay WidgetControllerClass is uninitialized ,  fill PKHudClass"))
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld() , OverlayWidgetClass);

	OverlayWidget = Cast<UPKUserWidget>(Widget);

	const FWidgetControllerParams WCParams(PC , PS , ASC , AS);

	UOverlayWidgetController* OverlayWC = GetOverlayWidgetController(WCParams);

	OverlayWidget->SetWidgetController(OverlayWC);

	OverlayWC->BroadcastInitialValues();
	
	Widget->AddToViewport();

	
}
