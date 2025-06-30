// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "UI/Widgets/PKUserWidget.h"

void UPKUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnAssignedWidgetController();
}
