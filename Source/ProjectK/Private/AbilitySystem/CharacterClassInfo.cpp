// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass Class) const
{
	return CharacterClassDefaultMap.FindChecked(Class);
}
