// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/WidgetController/PKWidgetController.h"

void UPKWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UPKWidgetController::BroadcastInitialValues()
{
	
}

void UPKWidgetController::BindCallbacksToDependencies()
{
}
