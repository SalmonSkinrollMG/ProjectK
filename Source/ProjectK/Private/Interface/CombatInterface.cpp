// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Interface/CombatInterface.h"


// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int ICombatInterface::GetPlayerLevel() const
{
	return 0;
}

FVector ICombatInterface::GetCombatSocketVector() const
{
	return FVector::ZeroVector;
}
